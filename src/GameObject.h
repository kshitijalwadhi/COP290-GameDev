#include "game.h"

class GameObject{

    public:
        GameObject(const char* textureSheet, int x, int y);
        ~GameObject();

        void render();
        void update();

        void updatePos(SDL_Event event);

    private:
        int xpos, ypos;
        int facing; // 0: up, 1: right, 2: down, 3: left
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;       
};
