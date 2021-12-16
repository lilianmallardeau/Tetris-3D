//
// Created by lilian on 16/11/2021.
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../parameters.h"
#include "NavigationGrid.h"
#include "../opengl/opengl_abstraction.hpp"

class Game {
    private:
        NavigationGrid grid;
        Bloc *activeBloc{};

        // OpenGL stuff
        glm::mat4 viewMatrix{}, projectionMatrix{};
        glm::mat4 viewProjMatrix{};

        std::vector<glm::mat4> wallsTransforms;
        VertexBuffer *wallsVertexBuffer{};
        IndexBuffer *wallsIndexBuffer{};
        VertexArray *wallsVertexArray{};
        Texture *wallsTexture{};
        Program *wallsShader{};

        VertexBuffer *blocVertexBuffer{};
        IndexBuffer *blocIndexBuffer{};
        VertexArray *blocVertexArray{};
        Texture *blocTexture{};
        Program *blocShader{};

        Game();

    public:
        Game(const Game&) = delete;
        static Game& getInstance() {
            static Game instance;
            return instance;
        };

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            getInstance().processKeyboardInput(key, action);
        };
        void processKeyboardInput(int key, int action);
        bool init();
        void gameLoop();

        void pushActiveBloc();

        [[nodiscard]] static Bloc* newRandomBloc();
        [[nodiscard]] bool checkForGameEnd() const {return false;};

        void computeWalls();

        void renderWalls();
        void renderBlocs();
        void renderActiveBloc();
};


#endif //GAME_H
