#include "game.h"
#include "globals.h"

Game *game = nullptr;

int main(int argc, char* argv[]) {
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Flag Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, false);

    while(game->running())
    {
        frameStart = SDL_GetTicks();

        if(!game->onMenu())
        {
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
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}