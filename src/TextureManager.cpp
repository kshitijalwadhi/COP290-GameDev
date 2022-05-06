#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fname)
{
    SDL_Surface* tempSur = IMG_Load(fname);
    if(tempSur == NULL)
    {
        printf("Unable to load image!");
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSur);
    SDL_FreeSurface(tempSur);
    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::drawBG(SDL_Texture* tex)
{
    SDL_RenderCopy(Game::renderer, tex, NULL, NULL);
}

SDL_Texture* TextureManager::loadTextureFromText(std::string text, const char* fontFile, int size, SDL_Color color)
{
    TTF_Font* font = TTF_OpenFont(fontFile, size);
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if(surf == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return tex;
}

void TextureManager::drawText(SDL_Texture* text, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, text, NULL, &dest);
}

SDL_Texture* TextureManager::progressBar(float progress, int maxProgress, SDL_Color bg_color, SDL_Color fg_color)
{
    SDL_Rect bg_rect;
    bg_rect.x = progress;
    bg_rect.y = 0;
    bg_rect.w = maxProgress-progress;
    bg_rect.h = 10;

    SDL_Rect fg_rect;
    fg_rect.x = 0;
    fg_rect.y = 0;
    fg_rect.w = progress;
    fg_rect.h = 10;

    SDL_Texture* tex = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, maxProgress, bg_rect.h);
    SDL_SetRenderTarget(Game::renderer, tex);
    SDL_SetRenderDrawColor(Game::renderer, fg_color.r, fg_color.g, fg_color.b, fg_color.a);
    SDL_RenderFillRect(Game::renderer, &fg_rect);
    SDL_SetRenderDrawColor(Game::renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderFillRect(Game::renderer, &bg_rect);
    SDL_SetRenderTarget(Game::renderer, NULL);
    return tex;
}

void TextureManager::drawProgressBar(SDL_Texture* tex, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}