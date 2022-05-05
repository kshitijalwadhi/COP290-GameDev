#include "game.h"

class TextureManager {

    public:
        static SDL_Texture* loadTexture(const char* fileName);
        static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
        static void drawBG(SDL_Texture* tex);
        static SDL_Texture* loadTextureFromText(const char* text, const char* fontFile, int size, SDL_Color color);
        static void drawText(SDL_Texture* text, SDL_Rect dest);
        static SDL_Texture* progressBar(float progress, int maxProgress, SDL_Color bg_color, SDL_Color fg_color);
        static void drawProgressBar(SDL_Texture* tex, SDL_Rect dest);
};