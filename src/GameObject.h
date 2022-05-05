#include "game.h"

class GameObject{

    public:
        GameObject(const char* textureSheet, int x, int y, int player_idx);
        ~GameObject();

        void render();
        void update();

        void updatePos(SDL_Event event, int map[40][80]);

    private:
        int player_idx;
        int xpos, ypos;
        int facing; // 0: up, 1: right, 2: down, 3: left
        int frames;

        int energy;
        int socialQuotient;
        int fitness;
        int nerdiness;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;       

        SDL_Texture* energyTex, *socialQuotientTex, *fitnessTex, *nerdinessTex;
        SDL_Rect dstRect_Energy, dstRect_SocialQuotient, dstRect_Fitness, dstRect_Nerdiness;     

        bool checkCollision(int x, int y, int map[40][80]);

};
