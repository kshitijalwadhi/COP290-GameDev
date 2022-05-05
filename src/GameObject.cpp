#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

SDL_Color bgColorBar = {0, 0, 0};
SDL_Color energyBarColor = {255, 0, 0};
SDL_Color socialQuotientBarColor = {0, 255, 0};
SDL_Color fitnessBarColor = {0, 0, 255};
SDL_Color nerdinessBarColor = {255, 255, 0};

GameObject::GameObject(const char* textureSheet, int x, int y, int player_idx, int character_type)
{
    player_idx = player_idx;
    character_type = character_type;

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

    int idx = character_type-1;
    int st_x, st_y; 
    st_y = 64 * (idx/4);
    st_x = 48 * (idx%4);

    spriteRects_D[0] = {st_x, st_y, 16, 16};
    spriteRects_D[1] = {st_x+16, st_y, 16, 16};
    spriteRects_D[2] = {st_x+32, st_y, 16, 16};

    spriteRects_L[0] = {st_x, st_y+16, 16, 16};
    spriteRects_L[1] = {st_x+16, st_y+16, 16, 16};
    spriteRects_L[2] = {st_x+32, st_y+16, 16, 16};
    
    spriteRects_R[0] = {st_x, st_y+32, 16, 16};
    spriteRects_R[1] = {st_x+16, st_y+32, 16, 16};
    spriteRects_R[2] = {st_x+32, st_y+32, 16, 16};

    spriteRects_U[0] = {st_x, st_y+48, 16, 16};
    spriteRects_U[1] = {st_x+16, st_y+48, 16, 16};
    spriteRects_U[2] = {st_x+32, st_y+48, 16, 16};
}

void GameObject::update()
{
    int idx = frames % 3;
    if(facing == 0)
    {
        srcRect = spriteRects_U[idx];
    }
    else if(facing == 1)
    {
        srcRect = spriteRects_R[idx];
    }
    else if(facing == 2)
    {
        srcRect = spriteRects_D[idx];
    }
    else if(facing == 3)
    {
        srcRect = spriteRects_L[idx];
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
    std::cout<<"xpos: "<<xpos<<" ypos: "<<ypos<<std::endl;
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