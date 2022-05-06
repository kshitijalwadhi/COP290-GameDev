#include "Enemy.h"
#include "TextureManager.h"
#include "globals.h"

Enemy::Enemy(const char* textureSheet, int x, int y, int character_type, Uint32 startTime)
{
    xpos = x;
    ypos = y;
    enemyDamper = 0;
    character_type = character_type;
    facing = 1;
    frames = 0;
    startTime = startTime;

    objTexture = TextureManager::loadTexture(textureSheet);

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

Enemy::~Enemy()
{
    SDL_DestroyTexture(objTexture);
}

void Enemy::update()
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
    frames = frames%3;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w*globals::SPRITE_SCALE;
    destRect.h = srcRect.h*globals::SPRITE_SCALE;
}

int returnEnemySpeed(int loc, int enemyDamper)
{
    int speed = 0;
    if(enemyDamper%globals::speedDampingFactor != 0)
        return speed;
    else
        enemyDamper = 0;
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

void Enemy::updatePosEnemy(int map[40][80])
{
    enemyDamper++;
    int tempy = (ypos+8)/16;
    int tempx = (xpos+0.5)/16;
    int loc = map[tempy][tempx];
    int hop = returnEnemySpeed(loc, enemyDamper);
    switch(facing)
    {
        case 0:
            if(!checkCollision(xpos,ypos-hop,map))
            {
                ypos -= hop;
            }
            else{
                facing = rand()%4;
            }
            break;
        case 1:
            if(!checkCollision(xpos+hop,ypos,map))
            {
                xpos += hop;
            }
            else{
                facing = rand()%4;
            }
            break;
        case 2:
            if(!checkCollision(xpos,ypos+hop,map))
            {
                ypos += hop;
            }
            else{
                facing = rand()%4;
            }
            break;
        case 3:
            if(!checkCollision(xpos-hop,ypos,map))
            {
                xpos -= hop;
            }
            else{
                facing = rand()%4;
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

void Enemy::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

bool checkValEnemy(int loc)
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

bool Enemy::checkCollision(int x, int y, int map[40][80])
{
    int tempy, tempx, loc;
    bool flag0, flag1, flag2, flag3;
    
    tempy = (y+8)/16;
    tempx = (x+0.5)/16;
    loc = map[tempy][tempx];
    flag0 = checkValEnemy(loc);
    
    tempy = (y+8)/16;
    tempx = (x+15.5)/16;
    loc = map[tempy][tempx];
    flag1 = checkValEnemy(loc);

    tempy = (y+15.5)/16;
    tempx = (x+0.5)/16;
    loc = map[tempy][tempx];
    flag2 = checkValEnemy(loc);

    tempy = (y+15.5)/16;
    tempx = (x+15.5)/16;
    loc = map[tempy][tempx];
    flag3 = checkValEnemy(loc);

    return flag0 || flag1 || flag2 || flag3;
}