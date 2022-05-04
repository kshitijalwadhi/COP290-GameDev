#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fname)
{
    SDL_Surface* tempSur = IMG_Load(fname);
    if(tempSur == NULL)
    {
        printf("Unable to load image!");
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSur);
    SDL_FreeSurface(tempSur);
    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

SDL_Texture* TextureManager::loadTextureFromText(const char* text, const char* fontFile, int size)
{
    TTF_Font* font = TTF_OpenFont(fontFile, size);
    SDL_Color color = {0, 0, 0};
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
    if(surf == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}