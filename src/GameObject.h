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
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;       
};
