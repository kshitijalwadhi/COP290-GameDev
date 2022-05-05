#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect spriteRects_L[WALKING_ANIMATION_FRAMES];
SDL_Rect spriteRects_R[WALKING_ANIMATION_FRAMES];

SDL_Color bgColorBar = {0, 0, 0};
SDL_Color energyBarColor = {255, 0, 0};
SDL_Color socialQuotientBarColor = {0, 255, 0};
SDL_Color fitnessBarColor = {0, 0, 255};
SDL_Color nerdinessBarColor = {255, 255, 0};

GameObject::GameObject(const char* textureSheet, int x, int y, int player_idx)
{
    player_idx = player_idx;

    objTexture = TextureManager::loadTexture(textureSheet);

    if(player_idx==1)
    {
        dstRect_Energy.x = dstRect_Fitness.x = dstRect_Nerdiness.x = dstRect_SocialQuotient.x = 0;
    }
    else{
        dstRect_Energy.x = dstRect_Fitness.x = dstRect_Nerdiness.x = dstRect_SocialQuotient.x = globals::SCREEN_WIDTH - 100;
    }
    dstRect_Energy.y = 0;
    dstRect_Fitness.y = 10;
    dstRect_Nerdiness.y = 20;
    dstRect_SocialQuotient.y = 30;
    dstRect_Energy.w = dstRect_Fitness.w = dstRect_Nerdiness.w = dstRect_SocialQuotient.w = 100;
    dstRect_Energy.h = dstRect_Fitness.h = dstRect_Nerdiness.h = dstRect_SocialQuotient.h = 10;

    xpos = x;
    ypos = y;

    energy = 50;
    socialQuotient = 10;
    fitness = 50;
    nerdiness = 30;

    energyTex = TextureManager::progressBar(energy, 100, bgColorBar, energyBarColor);
    socialQuotientTex = TextureManager::progressBar(socialQuotient, 100, bgColorBar, socialQuotientBarColor);
    fitnessTex = TextureManager::progressBar(fitness, 100, bgColorBar, fitnessBarColor);
    nerdinessTex = TextureManager::progressBar(nerdiness, 100, bgColorBar, nerdinessBarColor);

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

    energyTex = TextureManager::progressBar(energy, 100, bgColorBar, energyBarColor);
    socialQuotientTex = TextureManager::progressBar(socialQuotient, 100, bgColorBar, socialQuotientBarColor);
    fitnessTex = TextureManager::progressBar(fitness, 100, bgColorBar, fitnessBarColor);
    nerdinessTex = TextureManager::progressBar(nerdiness, 100, bgColorBar, nerdinessBarColor);
}

void GameObject::updatePos(SDL_Event event, int map[40][80])
{
    int hop;
    // if(map[(ypos/30)][(xpos/30)] == 0)
    // {
    //     hop = globals::WATER_SPEED;
    // }
    // else if(map[(ypos/30)][(xpos/30)] == 1)
    // {
    //     hop = globals::GRASS_SPEED;
    // }

    hop = globals::WATER_SPEED;

    switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (!checkCollision(xpos,ypos-hop-destRect.h, map))
                {
                    ypos -= hop;
                    facing = 0;
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (!checkCollision(xpos,ypos+hop+destRect.h, map))
                {
                    ypos += hop;
                    facing = 2;
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if(!checkCollision(xpos-hop-destRect.w,ypos, map))
                {
                    xpos -= hop;
                    facing = 3;
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if(!checkCollision(xpos+hop+destRect.w,ypos, map))
                {
                    xpos += hop;
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
    TextureManager::drawProgressBar(energyTex, dstRect_Energy);
    TextureManager::drawProgressBar(socialQuotientTex, dstRect_SocialQuotient);
    TextureManager::drawProgressBar(fitnessTex, dstRect_Fitness);
    TextureManager::drawProgressBar(nerdinessTex, dstRect_Nerdiness);
}

bool GameObject::checkCollision(int x, int y, int map[40][80])
{
    // adding temporarily:
    return false;
    int tempy = y/30;
    int tempx = x/30;
    if(map[tempy][tempx] == 2)
        return true;
    return false;
}