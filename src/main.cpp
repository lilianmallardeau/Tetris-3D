#include "game/Game.h"

int main() {
    Game& game = Game::getInstance();
    if (!game.init())
        return EXIT_FAILURE;

    game.gameLoop();

    return EXIT_SUCCESS;
}