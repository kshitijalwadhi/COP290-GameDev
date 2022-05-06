#include "GameObject.h"
#include "TextureManager.h"
#include "globals.h"

SDL_Color bgColorBar = {0, 0, 0};
SDL_Color energyBarColor = {255, 0, 0};
SDL_Color socialQuotientBarColor = {0, 255, 0};
SDL_Color fitnessBarColor = {0, 0, 255};
SDL_Color nerdinessBarColor = {255, 255, 0};

GameObject::GameObject(const char* textureSheet, int x, int y, int player_idx, int character_type, Uint32 startTime)
{
    player_idx = player_idx;
    character_type = character_type;
    startTime = startTime;

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
    facing = 1;

    energy = 80.0;
    socialQuotient = 10.0;
    fitness = 40.0;
    nerdiness = 30.0;

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

GameObject::~GameObject()
{
    SDL_DestroyTexture(objTexture);
    SDL_DestroyTexture(energyTex);
    SDL_DestroyTexture(socialQuotientTex);
    SDL_DestroyTexture(fitnessTex);
    SDL_DestroyTexture(nerdinessTex);
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

    energy -= globals::frameDelay * globals::energyDecay;

    energyTex = TextureManager::progressBar(energy, 100, bgColorBar, energyBarColor);
    socialQuotientTex = TextureManager::progressBar(socialQuotient, 100, bgColorBar, socialQuotientBarColor);
    fitnessTex = TextureManager::progressBar(fitness, 100, bgColorBar, fitnessBarColor);
    nerdinessTex = TextureManager::progressBar(nerdiness, 100, bgColorBar, nerdinessBarColor);
}

int returnSpeed(int loc)
{
    int speed = 0;
    for(int i=0; i<globals::ROAD_IDX.size();i++)
    {
        if(loc == globals::ROAD_IDX[i])
        {
            speed = globals::ROAD_SPEED;
            break;
        }
    }
    for(int i=0; i<globals::GRASS_IDX.size();i++)
    {
        if(loc == globals::GRASS_IDX[i])
        {
            speed = globals::GRASS_SPEED;
            break;
        }
    }
    for(int i=0; i<globals::TREE_IDX.size();i++)
    {
        if(loc == globals::TREE_IDX[i])
        {
            speed = globals::TREE_SPEED;
            break;
        }
    }
    return speed;
}

void GameObject::updatePos(SDL_Event event, const Uint8 *state, int map[40][80])
{
    int tempy = (ypos+8)/16;
    int tempx = (xpos+0.5)/16;
    int loc = map[tempy][tempx];
    int hop = returnSpeed(loc);

    if(state[SDL_SCANCODE_LSHIFT])
        hop = 1;
    switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                if (!checkCollision(xpos,ypos-hop, map))
                {
                    ypos -= hop;
                    facing = 0;
                }
                else{
                    int temp_hop = hop-1;
                    while(temp_hop>0)
                    {
                        if (!checkCollision(xpos,ypos-temp_hop, map))
                        {
                            ypos -= temp_hop;
                            facing = 0;
                        }
                        temp_hop--;
                    }
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (!checkCollision(xpos,ypos+hop, map))
                {
                    ypos += hop;
                    facing = 2;
                }
                else{
                    int temp_hop = hop-1;
                    while(temp_hop>0)
                    {
                        if (!checkCollision(xpos,ypos+temp_hop, map))
                        {
                            ypos += temp_hop;
                            facing = 2;
                        }
                        temp_hop--;
                    }
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if(!checkCollision(xpos-hop,ypos, map))
                {
                    xpos -= hop;
                    facing = 3;
                }
                else{
                    int temp_hop = hop-1;
                    while(temp_hop>0)
                    {
                        if(!checkCollision(xpos-temp_hop,ypos, map))
                        {
                            xpos -= temp_hop;
                            facing = 3;
                        }
                        temp_hop--;
                    }
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if(!checkCollision(xpos+hop,ypos, map))
                {
                    xpos += hop;
                    facing = 1;
                }
                else{
                    int temp_hop = hop-1;
                    while(temp_hop>0)
                    {
                        if(!checkCollision(xpos+temp_hop,ypos, map))
                        {
                            xpos += temp_hop;
                            facing = 1;
                        }
                        temp_hop--;
                    }
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

bool check(int loc)
{
    bool collision = true;
    for(int i=0; i<globals::ROAD_IDX.size();i++)
    {
        if(loc == globals::ROAD_IDX[i])
        {
            collision = false;
            break;
        }
    }
    for(int i=0; i<globals::GRASS_IDX.size();i++)
    {
        if(loc == globals::GRASS_IDX[i])
        {
            collision = false;
            break;
        }
    }
    for(int i=0; i<globals::TREE_IDX.size();i++)
    {
        if(loc == globals::TREE_IDX[i])
        {
            collision = false;
            break;
        }
    }
    return collision;
}

bool GameObject::checkCollision(int x, int y, int map[40][80])
{
    int tempy, tempx, loc;
    bool flag0, flag1, flag2, flag3;
    
    tempy = (y+8)/16;
    tempx = (x+0.5)/16;
    loc = map[tempy][tempx];
    flag0 = check(loc);
    
    tempy = (y+8)/16;
    tempx = (x+15.5)/16;
    loc = map[tempy][tempx];
    flag1 = check(loc);

    tempy = (y+15.5)/16;
    tempx = (x+0.5)/16;
    loc = map[tempy][tempx];
    flag2 = check(loc);

    tempy = (y+15.5)/16;
    tempx = (x+15.5)/16;
    loc = map[tempy][tempx];
    flag3 = check(loc);

    return flag0 || flag1 || flag2 || flag3;
}