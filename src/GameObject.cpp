#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y)
{
    renderer = ren;

    objTexture = TextureManager::loadTexture(textureSheet, renderer);

    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    xpos++;
    ypos++;

    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w*globals::SPRITE_SCALE;
    destRect.h = srcRect.h*globals::SPRITE_SCALE;
}

void GameObject::render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}