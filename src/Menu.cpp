#include "Menu.h"
#include "TextureManager.h"

const char* fontName_MenuScreenButtons = "../assets/fonts/Raleway-ExtraBold.ttf";
const int fontSize_MenuScreenButtons = 32;
SDL_Color buttonTextColor = {255, 255, 255};

Menu::Menu()
{
    dstRect_Play.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect_Play.y = globals::SCREEN_HEIGHT/2 - 200;
    dstRect_Play.w = 100;
    dstRect_Play.h = 100;

    dstRect_Exit.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect_Exit.y = globals::SCREEN_HEIGHT/2 - 50;
    dstRect_Exit.w = 100;
    dstRect_Exit.h = 100;

    dstRect_Music.x = globals::SCREEN_WIDTH - 100;
    dstRect_Music.y = 100;
    dstRect_Music.w = 50;
    dstRect_Music.h = 50;
    
}

void Menu::render()
{
    bg_tex = TextureManager::loadTexture("../assets/bg_images/menu.png");
    TextureManager::drawBG(bg_tex);
    SDL_DestroyTexture(bg_tex);

    SDL_Texture* button1_texture = TextureManager::loadTextureFromText("Play",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button1_texture,dstRect_Play);
    SDL_DestroyTexture(button1_texture);

    SDL_Texture* button2_texture = TextureManager::loadTextureFromText("Exit",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button2_texture,dstRect_Exit);
    SDL_DestroyTexture(button2_texture);

    SDL_Texture* button3_texture = TextureManager::loadTextureFromText("Toggle Music",fontName_MenuScreenButtons,fontSize_MenuScreenButtons, buttonTextColor);
    TextureManager::drawText(button3_texture,dstRect_Music);
    SDL_DestroyTexture(button3_texture);
}

void Menu::update()
{

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

    if(checkInside(x, y, dstRect_Play))
    {
        return 1;
    }
    else if(checkInside(x, y, dstRect_Exit))
    {
        return 2;
    }
    else if(checkInside(x, y, dstRect_Music))
    {
        return 3;
    }
    return 0;
}