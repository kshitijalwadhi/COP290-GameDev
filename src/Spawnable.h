#include "game.h"

class Spawnable{

    public:
        Spawnable(const char* textureSheet, int x, int y, int potion_type, int capacity);
        ~Spawnable();

        void update();
        void render();

        int getX();
        int getY();
        int getPotionType();
        int getCapacity();
        int potion_type;
        int capacity;
    private:
        int xpos, ypos;
        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
};