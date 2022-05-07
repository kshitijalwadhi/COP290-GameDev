#include "game.h"
#include "globals.h"
#include <time.h>

Game *game = nullptr;

int main(int argc, char* argv[]) {
    Uint32 frameStart;
    int frameTime;
    srand(time(0));
    game = new Game();

    game->init("Flag Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, false);

    while(game->running())
    {
        frameStart = SDL_GetTicks();

        if(!game->onMenu())
        {
            game->startTime = 0;
            game->handleEvents();
            game->update();
            game->render();
        }
        else{
            game->handleMenuEvents();
            game->updateMenu();
            game->renderMenu();
        }

        frameTime = SDL_GetTicks() - frameStart;

        // check if too fast, then delay frame
        if(globals::frameDelay > frameTime)
        {
            SDL_Delay(globals::frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}