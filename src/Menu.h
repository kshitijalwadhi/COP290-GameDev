#include "game.h"
#include "globals.h"

class Menu{

    public:
        Menu();
        ~Menu();

        void render();
        void update();

        int handleClick(SDL_Event event);
    private:
        SDL_Texture* bg_tex;

        SDL_Rect dstRect_PlaySingle;
        SDL_Rect dstRect_PlayMulti;
        SDL_Rect dstRect_Exit;

        SDL_Rect dstRect_Music;
        
};