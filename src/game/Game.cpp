//
// Created by lilian on 16/11/2021.
//

#include "Game.h"

#include <algorithm>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


Game::Game() : grid(NavigationGrid(ROWS, COLUMNS, DEPTH)), activeBloc(newRandomBloc()) {
    glm::vec3 cameraPosition(COLUMNS/2.0f, -6.5f, ROWS/2.0f);
    viewMatrix = glm::lookAt(
            cameraPosition,
            cameraPosition + glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
    );
    projectionMatrix = glm::perspective(glm::radians(FOV), ASPECT_RATIO, 1e-4f, DEPTH+10.0f);
    viewProjMatrix = projectionMatrix * viewMatrix;
}

bool Game::init() {
    srand(time(NULL)); //NOLINT(cert-msc51-cpp, modernize-use-nullptr)
    if (!Renderer::init(WINDOW_SIZE, "Tetris 3D", FULLSCREEN))
        return false;
    glEnable(GL_DEPTH_TEST);

    // --------- Face culling --------
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CW);
    // --------- Face culling --------

    // Key callback
    glfwSetKeyCallback(Renderer::context, Game::keyCallback);

    wallsVertexBuffer = new VertexBuffer;
    wallsIndexBuffer = new IndexBuffer;
    wallsVertexArray = new VertexArray;
    wallsTexture = new Texture(WALLS_TEXTURE);
    wallsShader = new Program("src/shaders/walls/vertexShader.glsl", "src/shaders/walls/fragmentShader.glsl");
    computeWalls();

    #include "cube.h"
    blocVertexBuffer = new VertexBuffer(6 * 4 * (3 + 2 + 3) * sizeof(float), cubeVertices);
    blocIndexBuffer = new IndexBuffer(6*6, cubeIndices);
    blocVertexArray = new VertexArray;
    blocTexture = new Texture(BLOCS_TEXTURE);
    blocShader = new Program("src/shaders/blocs/vertexShader.glsl", "src/shaders/blocs/fragmentShader.glsl");

    BufferLayout layout;
    layout.addAttribute<float>(3);
    layout.addAttribute<float>(2);
    layout.addAttribute<float>(3);
    wallsVertexArray->addBuffer(*wallsVertexBuffer, layout);
    blocVertexArray->addBuffer(*blocVertexBuffer, layout);

    wallsShader->setUniformMatrix4("u_viewProjMatrix", viewProjMatrix);
    blocShader->setUniformMatrix4("u_viewProjMatrix", viewProjMatrix);

    wallsTexture->Bind(0);
    blocTexture->Bind(1);
    wallsShader->setUniform<int>("u_texture", {0});
    blocShader->setUniform<int>("u_texture", {1});

    wallsShader->setUniform<float>("u_color", {WALLS_COLOR});
    return true;
}

void Game::processKeyboardInput(int key, int action) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(Renderer::context, GLFW_TRUE);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        if (grid.canMove(activeBloc, Direction::UP)) activeBloc->moveUp();
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        if (grid.canMove(activeBloc, Direction::DOWN)) activeBloc->moveDown();
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        if (grid.canMove(activeBloc, Direction::LEFT)) activeBloc->moveLeft();
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        if (grid.canMove(activeBloc, Direction::RIGHT)) activeBloc->moveRight();
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        pushActiveBloc();
}

void Game::gameLoop() {
    Renderer::setClearColor(BACKGROUND_COLOR);
    double lastPush = glfwGetTime();

    while (!glfwWindowShouldClose(Renderer::context)) {
        int windowWidth, windowHeight;
        glfwGetWindowSize(Renderer::context, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glfwPollEvents();

        if (!checkForGameEnd()) {
            if (grid.checkCollision(activeBloc)) {
                grid.solidify(activeBloc);
                free(activeBloc);
                activeBloc = newRandomBloc();
            }
            if (glfwGetTime() - lastPush > DELAY) {
                activeBloc->push();
                lastPush = glfwGetTime();
            }

            grid.removeFullSlices();

            // Rendering everything on the screen
            Renderer::Clear();
            renderWalls();
            renderBlocs();
            renderActiveBloc();

            glfwSwapBuffers(Renderer::context);
        }
    }
    glfwTerminate();
}

void Game::pushActiveBloc() {
    while (!grid.checkCollision(activeBloc))
        activeBloc->push();
}

Bloc* Game::newRandomBloc() {
    // NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp)
    switch (rand() % 4) {
        case 0: return new BasicBloc(ROWS, COLUMNS);
        case 1: return new BasicBloc(ROWS, COLUMNS);
        case 2: return new BasicBloc(ROWS, COLUMNS);
        case 3: return new BasicBloc(ROWS, COLUMNS);
    }
}

void Game::computeWalls() {
    wallsTransforms.reserve(ROWS*COLUMNS+ 2*DEPTH*(ROWS+COLUMNS));

    // Left and right sides
    glm::mat4 rotationRight = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    for (uint y = 0; y < DEPTH; ++y) {
        for (uint z = 0; z < ROWS; ++z) {
            wallsTransforms.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0, y, z)));
            wallsTransforms.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(COLUMNS, y+1, z))*rotationRight);
        }
    }
    // Bottom and top sides
    glm::mat4 rotationBottom = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationTop = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    for (uint x = 0; x < COLUMNS; ++x) {
        for (uint y = 0; y < DEPTH; ++y) {
            wallsTransforms.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(x+1, y, 0))*rotationBottom);
            wallsTransforms.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, ROWS))*rotationTop);
        }
    }
    // Back wall
    glm::mat4 rotationBack = glm::rotate(glm::mat4(1.0f), glm::radians(-90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    for (uint x = 0; x < COLUMNS; ++x)
        for (uint z = 0; z < ROWS; ++z)
            wallsTransforms.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(x, DEPTH, z))*rotationBack);

    float square[] = {
        // x     y      z                   u     v                      nx     ny    nz
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,   0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f,   1.0f, 1.0f,     1.0f, 0.0f, 0.0f
    };
    wallsVertexBuffer->setData(4*(3+2+3)*sizeof(float), square);

    unsigned int indices[] = {1, 0, 2, 2, 3, 1};
    wallsIndexBuffer->setData(6, indices);

    wallsShader->setUniformMatrix4("u_transforms", wallsTransforms.data(), wallsTransforms.size());
}

void Game::renderWalls() {
    Renderer::DrawInstances(*wallsVertexArray, *wallsIndexBuffer, *wallsShader, wallsTransforms.size());
}

void Game::renderBlocs() {
    std::vector<glm::vec3> translations;
    std::vector<glm::vec3> colors;
    uint blocCount = grid.countBlocs();
    translations.reserve(blocCount);
    colors.reserve(blocCount);
    for (uint slice = 0; slice < DEPTH; ++slice) {
        for (uint x = 0; x < COLUMNS; ++x) {
            for (uint z = 0; z < ROWS; ++z) {
                if (grid[{x, slice, z}]) {
                    translations.emplace_back(x, slice, z);
                    colors.emplace_back(grid.slicesColors[slice].r, grid.slicesColors[slice].g, grid.slicesColors[slice].b);
                }
            }
        }
    }
    blocShader->setUniform<float>("u_translations", translations.data(), translations.size());
    blocShader->setUniform<float>("u_slicesColors", colors.data(), colors.size());
    blocShader->setUniform<int>("u_drawActiveBlock", {0});
    Renderer::DrawInstances(*blocVertexArray, *blocIndexBuffer, *blocShader, blocCount);
}

void Game::renderActiveBloc() {
    blocShader->setUniform<int>("u_drawActiveBlock", {1});
    if (auto basicBloc = dynamic_cast<BasicBloc*>(activeBloc)) {
        glm::vec3 translation(basicBloc->position.x, basicBloc->position.y, basicBloc->position.z);
        blocShader->setUniform<float>("u_translations", &translation, 1);
        Renderer::Draw(*blocVertexArray, *blocIndexBuffer, *blocShader);
    }
    else if (auto complexBloc = dynamic_cast<ComplexBloc*>(activeBloc)) {
        std::vector<glm::vec3> translations;
        for (const BasicBloc& bloc : complexBloc->blocs) {
            translations.emplace_back(bloc.position.x, bloc.position.y, bloc.position.z);
        }
        blocShader->setUniform<float>("u_translations", translations.data(), translations.size());
        Renderer::DrawInstances(*blocVertexArray, *blocIndexBuffer, *blocShader, translations.size());
    }
    else throw std::bad_cast();
}
