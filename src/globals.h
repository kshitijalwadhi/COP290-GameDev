#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>

namespace globals {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;

	const float SPRITE_SCALE = 1.0f;

	const int GRASS_SPEED = 5;
	const int ROAD_SPEED = 7;

	const std::vector<int> GRASS_IDX = { 11, 12, 19, 20, 64, 65 };
	const std::vector<int> TREE_IDX = { 30, 38, 76, 77, 92 };
	const std::vector<int> ROAD_IDX = { 10, 18 }; 
}

#endif