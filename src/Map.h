#include "game.h"
#include <vector>
#include <map>

class Map{
    public:

        Map();
        ~Map();

        void loadMap(const char* fname);
        void drawMap();
        int map_mat[40][80];
        std::pair<int,int> validPos();

    private:

        SDL_Rect src, dest;
        SDL_Texture* textureMap;
};