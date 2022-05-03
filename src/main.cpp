#include "game.h"
#include "globals.h"

Game *game = nullptr;

int main(int argc, char* argv[]) {
    
    game = new Game();

    game->init("Flag Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, false);

    while(game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}