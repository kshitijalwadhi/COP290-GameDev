#include "Spawnable.h"
#include "TextureManager.h"
#include "globals.h"

Spawnable::Spawnable(const char* textureSheet, int x, int y, int potion_type, int capacity)
{
    xpos = x;
    ypos = y;
    potion_type = potion_type;
    capacity = capacity;

    objTexture = TextureManager::loadTexture(textureSheet);

    srcRect.x = (2+capacity)*16;
    srcRect.y = potion_type*16;
    srcRect.w = 16;
    srcRect.h = 16;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 16*globals::SPAWNABLE_SCALE;
    destRect.h = 16*globals::SPAWNABLE_SCALE;
}

Spawnable::~Spawnable()
{
    SDL_DestroyTexture(objTexture);
}

int Spawnable::getX()
{
    return xpos;
}

int Spawnable::getY()
{
    return ypos;
}

int Spawnable::getPotionType()
{
    return potion_type;
}

int Spawnable::getCapacity()
{
    return capacity;
}

void Spawnable::update()
{

}

void Spawnable::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}