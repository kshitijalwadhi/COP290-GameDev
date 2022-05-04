#include "Menu.h"
#include "TextureManager.h"

const char* fontName_MenuScreenButtons = "../assets/fonts/Raleway-ExtraBold.ttf";
const int fontSize_MenuScreenButtons = 32;

Menu::Menu()
{
    //ctor
}

void Menu::render()
{
    SDL_Texture* button1_texture = TextureManager::loadTextureFromText("Click here",fontName_MenuScreenButtons,fontSize_MenuScreenButtons);
    SDL_Rect dstRect;
    dstRect.x = globals::SCREEN_WIDTH/2 - 50;
    dstRect.y = globals::SCREEN_HEIGHT/2 - 50;
    dstRect.w = 100;
    dstRect.h = 100;
    TextureManager::drawText(button1_texture,dstRect);
}

void Menu::update()
{

}