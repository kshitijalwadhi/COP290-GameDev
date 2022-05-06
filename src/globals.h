#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>

namespace globals {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;

	const int FPS = 60;
    const int frameDelay = 1000 / FPS;

	const float SPRITE_SCALE = 1.0f;

	const int TREE_SPEED = 1;
	const int GRASS_SPEED = 2;
	const int ROAD_SPEED = 4;

	const std::vector<int> GRASS_IDX = { 12, 13, 20, 21, 65, 66 };
	const std::vector<int> TREE_IDX = { 31, 39, 77, 78, 93 };
	const std::vector<int> ROAD_IDX = { 11, 19 }; 

	const float energyDecay = 0.001;
	const int enemySpawnRate = 50;
	const int maxEnemies = 5;
}

#endif