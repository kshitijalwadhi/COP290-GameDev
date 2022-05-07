#include "Menu.h"
#include "TextureManager.h"

const char* fontName_MenuScreenButtons = "../assets/fonts/03314_BaarZeitgeist.ttf";
const int fontSize_MenuScreenButtons = 32;
SDL_Color buttonTextColor = {255, 255, 255};

Menu::Menu()
{
    dstRect_PlaySingle.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect_PlaySingle.y = globals::SCREEN_HEIGHT/2 - 250;
    dstRect_PlaySingle.w = 100;
    dstRect_PlaySingle.h = 75;

    dstRect_PlayMulti.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect_PlayMulti.y = globals::SCREEN_HEIGHT/2 - 150;
    dstRect_PlayMulti.w = 100;
    dstRect_PlayMulti.h = 75;

    dstRect_Exit.x = globals::SCREEN_WIDTH/2 - 25;
    dstRect_Exit.y = globals::SCREEN_HEIGHT/2 - 50;
    dstRect_Exit.w = 50;
    dstRect_Exit.h = 50;

    dstRect_Resume.x = globals::SCREEN_WIDTH/2 -25;
    dstRect_Resume.y = globals::SCREEN_HEIGHT/2 + 50;
    dstRect_Resume.w = 50;
    dstRect_Resume.h = 50;

    dstRect_Music.x = globals::SCREEN_WIDTH - 100;
    dstRect_Music.y = 100;
    dstRect_Music.w = 50;
    dstRect_Music.h = 50;

    isPaused = false;
    
}

void Menu::render()
{
    bg_tex = TextureManager::loadTexture("../assets/bg_images/menu.png");
    TextureManager::drawBG(bg_tex);
    SDL_DestroyTexture(bg_tex);

    SDL_Texture* button1_texture = TextureManager::loadTextureFromText("Single Player",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button1_texture,dstRect_PlaySingle);
    SDL_DestroyTexture(button1_texture);

    SDL_Texture* button2_texture = TextureManager::loadTextureFromText("Multi Player",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button2_texture,dstRect_PlayMulti);
    SDL_DestroyTexture(button2_texture);    

    SDL_Texture* button3_texture = TextureManager::loadTextureFromText("Exit",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button3_texture,dstRect_Exit);
    SDL_DestroyTexture(button3_texture);

    SDL_Texture* button4_texture = TextureManager::loadTextureFromText("Music",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button4_texture,dstRect_Music);
    SDL_DestroyTexture(button4_texture);
    
    if(!isPaused)
    {
        SDL_Texture* button5_texture = TextureManager::loadTextureFromText("Resume",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
        TextureManager::drawText(button5_texture,dstRect_Resume);
        SDL_DestroyTexture(button5_texture);
    }
}

void Menu::update(bool isPaused)
{
    isPaused = isPaused;
}

bool checkInside(int x, int y, SDL_Rect rect)
{
    if(x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        return true;
    }
    return false;
}

int Menu::handleClick(SDL_Event event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(checkInside(x, y, dstRect_PlaySingle))
    {
        return 1;
    }
    else if(checkInside(x, y, dstRect_PlayMulti))
    {
        return 2;
    }
    else if(checkInside(x, y, dstRect_Exit))
    {
        return 3;
    }
    else if(checkInside(x, y, dstRect_Music))
    {
        return 4;
    }
    else if(checkInside(x, y, dstRect_Resume) && !isPaused)
    {
        return 5;
    }
    return 0;
}