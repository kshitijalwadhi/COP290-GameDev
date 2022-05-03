#include "game.h"

class Map{
    public:

        Map();
        ~Map();

        void loadMap(int arr[20][25]);
        void drawMap();

        int map[20][25];

    private:

        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;
};