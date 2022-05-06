#include "game.h"

const int WALKING_ANIMATION_FRAMES_ENEMY = 3;

class Enemy{

    public:
        Enemy(const char* textureSheet, int x, int y, int character_type, Uint32 startTime);
        ~Enemy();

        void render();
        void update();

        void updatePosEnemy(int map[40][80]);

        int getX();
        int getY();
        
    private:
        int xpos, ypos;
        int enemyDamper;

        int character_type;
        int facing; // 0: up, 1: right, 2: down, 3: left
        int frames;
        Uint32 startTime;

        SDL_Rect spriteRects_L[WALKING_ANIMATION_FRAMES_ENEMY];
        SDL_Rect spriteRects_R[WALKING_ANIMATION_FRAMES_ENEMY];
        SDL_Rect spriteRects_U[WALKING_ANIMATION_FRAMES_ENEMY];
        SDL_Rect spriteRects_D[WALKING_ANIMATION_FRAMES_ENEMY];

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;       

        bool checkCollision(int x, int y, int map[40][80]);

};
