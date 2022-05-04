#include "Menu.h"
#include "TextureManager.h"

const char* fontName_MenuScreenButtons = "../assets/fonts/Raleway-ExtraBold.ttf";
const int fontSize_MenuScreenButtons = 32;

Menu::Menu()
{
    dstRect_Play.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect_Play.y = globals::SCREEN_HEIGHT/2 - 50;
    dstRect_Play.w = 100;
    dstRect_Play.h = 100;
}

void Menu::render()
{
    SDL_Texture* button1_texture = TextureManager::loadTextureFromText("Click here",fontName_MenuScreenButtons,fontSize_MenuScreenButtons);

    TextureManager::drawText(button1_texture,dstRect_Play);
}

void Menu::update()
{

}

int Menu::handleClick(SDL_Event event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > dstRect_Play.x && x < dstRect_Play.x + dstRect_Play.w && y > dstRect_Play.y && y < dstRect_Play.y + dstRect_Play.h)
    {
        return 1;
    }

    return 0;
}