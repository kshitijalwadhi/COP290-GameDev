#include "game.h"
#include "globals.h"

class Menu{

    public:
        Menu();
        ~Menu();

        void render();
        void update(bool isPaused);

        int handleClick(SDL_Event event);
        bool isPaused;
    private:
        SDL_Texture* bg_tex;

        SDL_Rect dstRect_PlaySingle;
        SDL_Rect dstRect_PlayMulti;
        SDL_Rect dstRect_Exit;
        SDL_Rect dstRect_Resume;

        SDL_Rect dstRect_Music;
        
};