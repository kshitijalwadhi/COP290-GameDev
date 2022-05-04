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
        SDL_Rect dstRect_Play;
        
};