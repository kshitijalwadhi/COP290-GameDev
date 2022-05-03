#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::loadTexture(textureSheet);

    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w*globals::SPRITE_SCALE;
    destRect.h = srcRect.h*globals::SPRITE_SCALE;
}

void GameObject::updatePos(SDL_Event event)
{
    switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                ypos -= 5;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                ypos += 5;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                xpos -= 5;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                xpos += 5;
                break;
        }
        if(xpos <0)
            xpos = 0;
        if(ypos <0)
            ypos = 0;
        if(xpos > globals::SCREEN_WIDTH - destRect.w)
            xpos = globals::SCREEN_WIDTH - destRect.w;
        if(ypos > globals::SCREEN_HEIGHT - destRect.h)
            ypos = globals::SCREEN_HEIGHT - destRect.h;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}