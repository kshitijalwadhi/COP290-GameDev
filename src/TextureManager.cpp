#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fname, SDL_Renderer* renderer)
{
    SDL_Surface* tempSur = IMG_Load(fname);
    if(tempSur == NULL)
    {
        printf("Unable to load image!");
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSur);
    SDL_FreeSurface(tempSur);
    return tex;
}