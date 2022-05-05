#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>

Map::Map(){
    dirt = TextureManager::loadTexture("../assets/maps/dirt.png");
    grass = TextureManager::loadTexture("../assets/maps/grass.png");
    water = TextureManager::loadTexture("../assets/maps/water.png");

    loadMap("../assets/maps/map.txt");

    src.x = src.y = 0;
    src.w = dest.w = 16;
    src.h = dest.h = 16;

    dest.x = dest.y = 0;
}

void Map::loadMap(const char* fname){
    std::vector<std::vector<int>> mat;
    std::ifstream file(fname);
    std::string line;
    
    while(std::getline(file, line)){
        std::vector<int> row;
        std::stringstream ss(line);
        std::string temp;

        while(std::getline(ss, temp, ',')){
            row.push_back(std::stoi(temp));
        }
        mat.push_back(row);
    }

    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 80; j++){
            map[i][j] = mat[i][j];
        }
    }
}

void Map::drawMap(){
    int type = 0;

    for(int i=0; i<40; i++){
        for(int j=0; j<80; j++){
            type = map[i][j];

            src.x = src.y = 0;
            src.w = dest.w = dest.h = 16;
            dest.x = j * 16;
            dest.y = i * 16;

            switch(type){
                case 0:
                    TextureManager::draw(water, src, dest);
                    break;
                case 1:
                    TextureManager::draw(grass, src, dest);
                    break;
                default:
                    TextureManager::draw(dirt, src, dest);
                    break;
            }
        }
    }
}