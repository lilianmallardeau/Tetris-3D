cmake_minimum_required(VERSION 3.20)
project(Tetris_3D)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

add_compile_options(-Wall -Wextra)

add_executable(Tetris_3D src/main.cpp src/opengl/BufferLayout.cpp src/opengl/BufferLayout.h src/opengl/IndexBuffer.cpp src/opengl/IndexBuffer.h src/opengl/opengl_abstraction.hpp src/opengl/Program.cpp src/opengl/Program.h src/opengl/Renderer.cpp src/opengl/Renderer.h src/opengl/Shader.cpp src/opengl/Shader.h src/opengl/Texture.cpp src/opengl/Texture.h src/opengl/VertexArray.cpp src/opengl/VertexArray.h src/opengl/VertexBuffer.cpp src/opengl/VertexBuffer.h src/game/Game.cpp src/game/Game.h src/parameters.h src/game/NavigationGrid.cpp src/game/NavigationGrid.h src/game/blocs/Bloc.cpp src/game/blocs/Bloc.h src/game/blocs/BasicBloc.cpp src/game/blocs/BasicBloc.h src/game/blocs/ComplexBloc.cpp src/game/blocs/ComplexBloc.h src/game/cube.h)

target_include_directories(Tetris_3D PRIVATE lib/)

target_link_libraries(Tetris_3D
	PRIVATE
	glad
	glfw
	glm
	OpenGL::GL)
