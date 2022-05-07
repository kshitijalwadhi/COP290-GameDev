#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>

class Game{
    public:
        Game();
        ~Game();
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void clean();

        void updateStatusText();

        void handleMenuEvents();
        void updateMenu();
        void renderMenu();

        void enemySpawnHelper();
        void spawnableSpawnHelper();

        void checkSpawnableIntersection();
        void checkEnemyInteraction();

        bool running() { return isRunning; }
        bool onMenu() {return isMenuScreen;}
        static SDL_Renderer* renderer;

        Uint32 startTime;

    private:
        bool isRunning;
        bool isMenuScreen;
        bool bgMusicPlaying;

        bool isMultiplayer;
        bool gameOver;

        int numEnemies, numSpawnables;
        SDL_Window* window;
};

#endif