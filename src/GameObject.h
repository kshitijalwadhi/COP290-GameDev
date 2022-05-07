#include "game.h"
#include <vector>

const int WALKING_ANIMATION_FRAMES = 3;

class GameObject{

    public:
        GameObject(const char* textureSheet, int x, int y, int player_idx, int character_type, Uint32 startTime);
        ~GameObject();

        int getX();
        int getY();

        void render();
        void update(int map[40][80]);

        void updatePos(SDL_Event event, const Uint8 *state, int map[40][80], int player_idx);

        void updateAttrs(int map[40][80]);

        bool checkAndHandleSpawnableIntersection(int x_spawn, int y_spawn, int type, int capacity);

        bool checkAndHandleEnemyIntersection(int x_enemy, int y_enemy);

        bool isAlive();
    private:
        int xpos, ypos;
        
        int player_idx;
        int character_type;
        int facing; // 0: up, 1: right, 2: down, 3: left
        int frames;
        Uint32 startTime;

        Uint32 lastEnemyInteraction;

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

        SDL_Texture* energyLabelTex, *socialQuotientLabelTex, *fitnessLabelTex, *nerdinessLabelTex;

        SDL_Rect dstRect_EnergyLabel, dstRect_SocialQuotientLabel, dstRect_FitnessLabel, dstRect_NerdinessLabel;

        bool checkCollision(int x, int y, int map[40][80]);

};
