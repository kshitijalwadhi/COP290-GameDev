#include "Map.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include "globals.h"

Map::Map(){
    textureMap = TextureManager::loadTexture("../assets/maps/basictiles.png");

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
            map_mat[i][j] = mat[i][j];
        }
    }
}

void Map::drawMap(){
    int idx = 0;
    int r=0,c=0;
    for(int i=0; i<40; i++){
        for(int j=0; j<80; j++){
            idx = map_mat[i][j]-1;

            r = idx/8;
            c = idx%8;

            src.x = c*16;
            src.y = r*16;
            src.w = 16;
            src.h = 16;

            dest.w = dest.h = 16;
            dest.x = j * 16;
            dest.y = i * 16;

            TextureManager::draw(textureMap, src, dest);
        }
    }
}

bool checkValid(int loc)
{
    bool valid = false;
    for(int i=0; i<globals::ROAD_IDX.size();i++)
    {
        if(loc == globals::ROAD_IDX[i])
        {
            valid = true;
            break;
        }
    }
    for(int i=0; i<globals::GRASS_IDX.size();i++)
    {
        if(loc == globals::GRASS_IDX[i])
        {
            valid = true;
            break;
        }
    }
    return valid;
}

std::pair<int,int> Map::validPos(){
    int r, c, loc;
    while(true){
        r = rand() % 40;
        c = rand() % 80;
        loc = map_mat[r][c];
        if(checkValid(loc)){
            return std::make_pair(c,r);
        }
    }
}