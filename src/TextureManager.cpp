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