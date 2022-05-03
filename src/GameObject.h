#include "game.h"

class GameObject{

    public:
        GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y);
        ~GameObject();

        void render();
        void update();

    private:
        int xpos, ypos;

        SDL_Texture* objTexture;
        SDL_Renderer* renderer; 
        SDL_Rect srcRect, destRect;       
};
