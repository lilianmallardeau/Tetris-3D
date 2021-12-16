#ifndef PARAMETERS_H
#define PARAMETERS_H

// Full screen mode and window settings
#define FULLSCREEN                  1
#define WINDOW_SIZE                 1000, 700 // Not used if FULLSCREEN is set to 1

// GAME PARAMETERS
#define ROWS                        5
#define COLUMNS                     5
#define DEPTH                       10
#define DELAY                       1

// TEXTURES AND APPEARANCE
#define BACKGROUND_COLOR            0.0f, 0.0f, 0.0f
#define WALLS_COLOR                 0.27f, 0.3f, 0.56f
#define WALLS_TEXTURE               "assets/textures/wall.png"
#define BLOCS_TEXTURE               "assets/textures/bloc.png"

// CAMERA & VIEW
#define FOV                         45.0f
#define ASPECT_RATIO                4.0f / 3.0f


#endif //PARAMETERS_H
