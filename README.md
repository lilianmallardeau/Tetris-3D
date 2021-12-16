# Tetris 3D
3D tetris, made with C++ and OpenGL

![tetris_3d_screenshot](https://user-images.githubusercontent.com/56023249/146317937-14b3d12a-2267-453c-9bea-ad9d78941237.png)


## Clone

Clone the repository with the `recurse-submodules` option to clone the libraries repositories as well: 
```
git clone --recurse-submodules https://github.com/lilianmallardeau/Tetris-3D.git
```
Then move to the cloned folder.

## Build and run
```
mkdir build
cd build
cmake ..
make
cd ..
./build/Tetris_3D
```
To run, the current working directory **MUST** be the root folder of the repository, because the program has to load the shaders files in the `src/shaders/` folder and the textures in the `assets/` folder.

## Changing the game options
Some game options can be changed in the `src/parameters.h` header file. Although their name is already kind of explicit, here is a brief description of each of them:

| Parameter | Description |
|:---------:|:-----------:|
| `FULLSCREEN` | 1 to enable fullscreen, 0 otherwise |
| `WINDOW_SIZE` | Size of the window if fullscreen is disabled. Ignored if `FULSCREEN` is set to 1. |
| `ROWS` | Number of rows for the map |
| `COLUMNS` | Number of columns for the map |
| `DEPTH` | Depth of the map |
| `DELAY` | Delay (in seconds) between each automatic forward of the active block |
| `BACKGROUND_COLOR` | Background color |
| `WALLS_COLOR` | Color of the walls, blended with the texture |
| `WALLS_TEXTURE` | Texture for the walls |
| `BLOCS_TEXTURE` | Texture for the blocks |
| `FOV` | Field of view of the camera (degrees) |
| `ASPECT_RATIO` | Aspect ratio of the window / screen |
