#include "game.h"

class Spawnable{

    public:
        Spawnable(const char* textureSheet, int x, int y, int potion_type, int capacity);
        ~Spawnable();

        void update();
        void render();
    private:
        int xpos, ypos;
        int potion_type;
        int capacity;
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
};