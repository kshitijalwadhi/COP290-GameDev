#include "game.h"

class TextureManager {

    public:
        static SDL_Texture* loadTexture(const char* fileName);
        static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
        static SDL_Texture* loadTextureFromText(const char* text, const char* fontFile, int size);
};