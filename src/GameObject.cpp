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

    money = 1000;

    objTexture = TextureManager::loadTexture(textureSheet);

    if(player_idx==1)
    {
        dstRect_Energy.x = dstRect_Fitness.x = dstRect_Nerdiness.x = dstRect_SocialQuotient.x = dstRect_Money.x = 35*16;
        dstRect_EnergyLabel.x = dstRect_FitnessLabel.x = dstRect_NerdinessLabel.x = dstRect_SocialQuotientLabel.x = dstRect_MoneyLabel.x = 30*16;
    }
    else{
        dstRect_Energy.x = dstRect_Fitness.x = dstRect_Nerdiness.x = dstRect_SocialQuotient.x = dstRect_Money.x = 69*16;
        dstRect_EnergyLabel.x = dstRect_FitnessLabel.x = dstRect_NerdinessLabel.x = dstRect_SocialQuotientLabel.x = dstRect_MoneyLabel.x = 64*16;
    }
    dstRect_Energy.y = 31*16;
    dstRect_Fitness.y = dstRect_Energy.y + 10;
    dstRect_Nerdiness.y = dstRect_Fitness.y + 10;
    dstRect_SocialQuotient.y = dstRect_Nerdiness.y + 10;
    dstRect_Energy.w = dstRect_Fitness.w = dstRect_Nerdiness.w = dstRect_SocialQuotient.w = 100;
    dstRect_Energy.h = dstRect_Fitness.h = dstRect_Nerdiness.h = dstRect_SocialQuotient.h = 10;

    dstRect_EnergyLabel.y = dstRect_Energy.y;
    dstRect_FitnessLabel.y = dstRect_Fitness.y;
    dstRect_NerdinessLabel.y = dstRect_Nerdiness.y;
    dstRect_SocialQuotientLabel.y = dstRect_SocialQuotient.y;
    dstRect_EnergyLabel.w = dstRect_FitnessLabel.w = dstRect_NerdinessLabel.w = dstRect_SocialQuotientLabel.w = 50;
    dstRect_EnergyLabel.h = dstRect_FitnessLabel.h = dstRect_NerdinessLabel.h = dstRect_SocialQuotientLabel.h = 10;

    dstRect_Money.y = dstRect_SocialQuotient.y + 15;
    dstRect_Money.w = dstRect_MoneyLabel.w = 50;
    dstRect_Money.h = dstRect_MoneyLabel.h = 10;
    dstRect_MoneyLabel.y = dstRect_Money.y;

    energy = 80.0;
    socialQuotient = 10.0;
    fitness = 40.0;
    nerdiness = 30.0;

    energyTex = TextureManager::progressBar(energy, 100, bgColorBar, energyBarColor);
    socialQuotientTex = TextureManager::progressBar(socialQuotient, 100, bgColorBar, socialQuotientBarColor);
    fitnessTex = TextureManager::progressBar(fitness, 100, bgColorBar, fitnessBarColor);
    nerdinessTex = TextureManager::progressBar(nerdiness, 100, bgColorBar, nerdinessBarColor);

    moneyTex = TextureManager::loadTextureFromText(std::to_string(money), "../assets/fonts/Raleway-Medium.ttf", 16, {255, 255, 255});

    energyLabelTex = TextureManager::loadTextureFromText("Energy", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    socialQuotientLabelTex = TextureManager::loadTextureFromText("Social Quotient", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    fitnessLabelTex = TextureManager::loadTextureFromText("Fitness", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    nerdinessLabelTex = TextureManager::loadTextureFromText("Nerdiness", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    moneyLabelTex = TextureManager::loadTextureFromText("Money: $", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});

    xpos = x;
    ypos = y;
    facing = 1;

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
    SDL_DestroyTexture(moneyTex);
    SDL_DestroyTexture(energyLabelTex);
    SDL_DestroyTexture(socialQuotientLabelTex);
    SDL_DestroyTexture(fitnessLabelTex);
    SDL_DestroyTexture(nerdinessLabelTex);
    SDL_DestroyTexture(moneyLabelTex);
}

int GameObject::getX(){
    return xpos;
}

int GameObject::getY(){
    return ypos;
}

void GameObject::update(int map[40][80])
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

    updateAttrs(map);

    energyTex = TextureManager::progressBar(energy, 100, bgColorBar, energyBarColor);
    socialQuotientTex = TextureManager::progressBar(socialQuotient, 100, bgColorBar, socialQuotientBarColor);
    fitnessTex = TextureManager::progressBar(fitness, 100, bgColorBar, fitnessBarColor);
    nerdinessTex = TextureManager::progressBar(nerdiness, 100, bgColorBar, nerdinessBarColor);

    moneyTex = TextureManager::loadTextureFromText(std::to_string(money), "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    energyLabelTex = TextureManager::loadTextureFromText("Energy", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    socialQuotientLabelTex = TextureManager::loadTextureFromText("Social Quotient", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    fitnessLabelTex = TextureManager::loadTextureFromText("Fitness", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    nerdinessLabelTex = TextureManager::loadTextureFromText("Nerdiness", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
    moneyLabelTex = TextureManager::loadTextureFromText("Money: $", "../assets/fonts/Raleway-Medium.ttf", 8, {255, 255, 255});
}

bool GameObject::checkAndHandleSpawnableIntersection(int x_spawn, int y_spawn, int type, int capacity)
{
    bool intersect = false;
    int x_spawn_centre = x_spawn + 8;
    int y_spawn_centre = y_spawn + 8;
    if(xpos<=x_spawn_centre && x_spawn_centre<=xpos+16 && ypos<=y_spawn_centre && y_spawn_centre<=ypos+16)
    {
        intersect = true;
    }
    if(intersect)
    {
        std::cout<<"Type: "<< type << " Capacity: " << capacity << std::endl;
        int actualCap;
        if(capacity == 1)
            actualCap = 100;
        else if(capacity == 2)
            actualCap = 50;
        else if(capacity == 3)
            actualCap = 25;
        if(type == 0)
        {
            if(energy < 100)
            {
                energy += actualCap;
                if(energy > 100)
                {
                    energy = 100;
                }
            }
        }
        else if(type == 1)
        {
            if(socialQuotient < 100)
            {
                socialQuotient += actualCap;
                if(socialQuotient > 100)
                {
                    socialQuotient = 100;
                }
            }
        }
        else if(type == 2)
        {
            if(fitness < 100)
            {
                fitness += actualCap;
                if(fitness > 100)
                {
                    fitness = 100;
                }
            }
        }
        else if(type == 3)
        {
            if(nerdiness < 100)
            {
                nerdiness += actualCap;
                if(nerdiness > 100)
                {
                    nerdiness = 100;
                }
            }
        }
    }
    return intersect;
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
    for(auto pos:globals::BUILDINGS_IDX)
    {
        if(loc == pos)
        {
            speed = globals::BUILDING_SPEED;
            break;
        }
    }
    return speed;
}

void GameObject::updatePos(SDL_Event event, const Uint8 *state, int map[40][80], int player_idx)
{
    int tempy = (ypos+8)/16;
    int tempx = (xpos+0.5)/16;
    int loc = map[tempy][tempx];
    int hop = returnSpeed(loc);

    if(state[SDL_SCANCODE_LSHIFT])
        hop = 1;

    if(player_idx == 1)
    {
        if(state[SDL_SCANCODE_W])
        {
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
            frames++;
        }
        if(state[SDL_SCANCODE_S])
        {
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
            frames++;
        }
        if(state[SDL_SCANCODE_A])
        {
            if (!checkCollision(xpos-hop,ypos, map))
            {
                xpos -= hop;
                facing = 3;
            }
            else{
                int temp_hop = hop-1;
                while(temp_hop>0)
                {
                    if (!checkCollision(xpos-temp_hop,ypos, map))
                    {
                        xpos -= temp_hop;
                        facing = 3;
                    }
                    temp_hop--;
                }
            }
            frames++;
        }
        if(state[SDL_SCANCODE_D])
        {
            if (!checkCollision(xpos+hop,ypos, map))
            {
                xpos += hop;
                facing = 1;
            }
            else{
                int temp_hop = hop-1;
                while(temp_hop>0)
                {
                    if (!checkCollision(xpos+temp_hop,ypos, map))
                    {
                        xpos += temp_hop;
                        facing = 1;
                    }
                    temp_hop--;
                }
            }
            frames++;
        }
    }
    else{
        if(state[SDL_SCANCODE_UP])
        {
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
            frames++;
        }
        if(state[SDL_SCANCODE_DOWN])
        {
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
            frames++;
        }
        if(state[SDL_SCANCODE_LEFT])
        {
            if (!checkCollision(xpos-hop,ypos, map))
            {
                xpos -= hop;
                facing = 3;
            }
            else{
                int temp_hop = hop-1;
                while(temp_hop>0)
                {
                    if (!checkCollision(xpos-temp_hop,ypos, map))
                    {
                        xpos -= temp_hop;
                        facing = 3;
                    }
                    temp_hop--;
                }
            }
            frames++;
        }
        if(state[SDL_SCANCODE_RIGHT])
        {
            if (!checkCollision(xpos+hop,ypos, map))
            {
                xpos += hop;
                facing = 1;
            }
            else{
                int temp_hop = hop-1;
                while(temp_hop>0)
                {
                    if (!checkCollision(xpos+temp_hop,ypos, map))
                    {
                        xpos += temp_hop;
                        facing = 1;
                    }
                    temp_hop--;
                }
            }
            frames++;
        }
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

    TextureManager::drawProgressBar(energyTex, dstRect_Energy);
    TextureManager::drawProgressBar(socialQuotientTex, dstRect_SocialQuotient);
    TextureManager::drawProgressBar(fitnessTex, dstRect_Fitness);
    TextureManager::drawProgressBar(nerdinessTex, dstRect_Nerdiness);
    SDL_RenderCopy(Game::renderer, energyLabelTex, NULL, &dstRect_EnergyLabel);
    SDL_RenderCopy(Game::renderer, socialQuotientLabelTex, NULL, &dstRect_SocialQuotientLabel);
    SDL_RenderCopy(Game::renderer, fitnessLabelTex, NULL, &dstRect_FitnessLabel);
    SDL_RenderCopy(Game::renderer, nerdinessLabelTex, NULL, &dstRect_NerdinessLabel);
    SDL_RenderCopy(Game::renderer, moneyLabelTex, NULL, &dstRect_MoneyLabel);
    SDL_RenderCopy(Game::renderer, moneyTex, NULL, &dstRect_Money);

    SDL_DestroyTexture(energyTex);
    SDL_DestroyTexture(socialQuotientTex);
    SDL_DestroyTexture(fitnessTex);
    SDL_DestroyTexture(nerdinessTex);
    SDL_DestroyTexture(moneyTex);
    SDL_DestroyTexture(energyLabelTex);
    SDL_DestroyTexture(moneyLabelTex);
    SDL_DestroyTexture(socialQuotientLabelTex);
    SDL_DestroyTexture(fitnessLabelTex);
    SDL_DestroyTexture(nerdinessLabelTex);
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
    for(auto pos: globals::BUILDINGS_IDX)
    {
        if(loc == pos)
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

/*
0: Rest
1: Hostel
2: Food
3: SAC
4: Study
*/
int getPosn(int x, int y, int map[40][80])
{
    int tempy, tempx, loc;
    tempy = (y+8)/16;
    tempx = (x+0.5)/16;
    loc = map[tempy][tempx];

    for(auto idx:globals::HOSTEL_IDX)
    {
        if(loc == idx)
            return 1;
    }

    for(auto idx:globals::FOOD_IDX)
    {
        if(loc == idx)
            return 2;
    }

    for(auto idx:globals::SAC_IDX)
    {
        if(loc == idx)
            return 3;
    }

    for(auto idx:globals::STUDY_IDX)
    {
        if(loc == idx)
            return 4;
    }

    return 0;
}

void GameObject::updateAttrs(int map[40][80])
{
    int loc = getPosn(xpos, ypos, map);

    energy -= globals::frameDelay * globals::energyDecay;
    socialQuotient -= globals::frameDelay * globals::socialQuotientDecay;
    fitness -= globals::frameDelay * globals::fitnessDecay;
    nerdiness -= globals::frameDelay * globals::nerdinessDecay;
    if(energy < 0)
        energy = 0;
    if(socialQuotient < 0)
        socialQuotient = 0;
    if(fitness < 0)
        fitness = 0;
    if(nerdiness < 0)
        nerdiness = 0;

    if(loc == 1)
    {
        energy += globals::frameDelay * globals::energyGain;
    }
    else if(loc == 2)
    {
        energy += globals::frameDelay * globals::energyGain;
    }
    else if(loc == 3)
    {
        socialQuotient += globals::frameDelay * globals::socialQuotientGain;
    }
    else if(loc == 4)
    {
        nerdiness += globals::frameDelay * globals::nerdinessGain;
    }
}
