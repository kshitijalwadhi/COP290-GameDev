#include "game.h"

const int WALKING_ANIMATION_FRAMES = 3;

class GameObject{

    public:
        GameObject(const char* textureSheet, int x, int y, int player_idx, int character_type, Uint32 startTime, bool isEnemy);
        ~GameObject();

        void render();
        void update();

        void updatePos(SDL_Event event, const Uint8 *state, int map[40][80]);
        void updatePosEnemy(int map[40][80]);
        
    private:
        int xpos, ypos;

        bool isEnemy;
        
        int player_idx;
        int character_type;
        int facing; // 0: up, 1: right, 2: down, 3: left
        int frames;
        Uint32 startTime;

        float energy;
        float socialQuotient;
        float fitness;
        float nerdiness;

        SDL_Rect spriteRects_L[WALKING_ANIMATION_FRAMES];
        SDL_Rect spriteRects_R[WALKING_ANIMATION_FRAMES];
        SDL_Rect spriteRects_U[WALKING_ANIMATION_FRAMES];
        SDL_Rect spriteRects_D[WALKING_ANIMATION_FRAMES];

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;       

        SDL_Texture* energyTex, *socialQuotientTex, *fitnessTex, *nerdinessTex;
        SDL_Rect dstRect_Energy, dstRect_SocialQuotient, dstRect_Fitness, dstRect_Nerdiness;     

        bool checkCollision(int x, int y, int map[40][80]);

};
