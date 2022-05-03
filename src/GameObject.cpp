#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect spriteRects_L[WALKING_ANIMATION_FRAMES];
SDL_Rect spriteRects_R[WALKING_ANIMATION_FRAMES];

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::loadTexture(textureSheet);

    xpos = x;
    ypos = y;

    frames = 0;

    spriteRects_L[0] = {0, 0, 16, 16};
    spriteRects_L[1] = {16, 0, 16, 16};
    spriteRects_L[2] = {32, 0, 16, 16};
    spriteRects_L[3] = {48, 0, 16, 16};
    spriteRects_L[4] = {64, 0, 16, 16};
    spriteRects_L[5] = {80, 0, 16, 16};

    spriteRects_R[0] = {0, 16, 16, 16};
    spriteRects_R[1] = {16, 16, 16, 16};
    spriteRects_R[2] = {32, 16, 16, 16};
    spriteRects_R[3] = {48, 16, 16, 16};
    spriteRects_R[4] = {64, 16, 16, 16};
    spriteRects_R[5] = {80, 16, 16, 16};
}

void GameObject::update()
{
    int idx = frames % 6;
    if(facing == 3 || facing == 2)
    {
        srcRect = spriteRects_L[idx];
    }
    else
    {   
        srcRect = spriteRects_R[idx];
    }

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w*globals::SPRITE_SCALE;
    destRect.h = srcRect.h*globals::SPRITE_SCALE;
}

void GameObject::updatePos(SDL_Event event, int map[20][25])
{
    switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (!checkCollision(xpos,ypos-5-destRect.h, map))
                {
                    ypos -= 5;
                    facing = 0;
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (!checkCollision(xpos,ypos+5+destRect.h, map))
                {
                    ypos += 5;
                    facing = 2;
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if(!checkCollision(xpos-5-destRect.w,ypos, map))
                {
                    xpos -= 5;
                    facing = 3;
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if(!checkCollision(xpos+5+destRect.w,ypos, map))
                {
                    xpos += 5;
                    facing = 1;
                }
                break;
        }
    frames++;
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

bool GameObject::checkCollision(int x, int y, int map[20][25])
{
    int tempy = y/30;
    int tempx = x/30;
    if(map[tempy][tempx] == 2)
        return true;
    return false;
}