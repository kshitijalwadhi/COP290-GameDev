#include "Menu.h"
#include "TextureManager.h"

Menu::Menu()
{
    //ctor
}

void Menu::render()
{
    const char* fontName = "../assets/fonts/Raleway-ExtraBold.ttf";
    int fontSize = 32;
    SDL_Texture* button1_texture = TextureManager::loadTextureFromText("Click here",fontName,32);
    SDL_RenderCopy(Game::renderer, button1_texture, NULL, NULL);
}

void Menu::update()
{

}