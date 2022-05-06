#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>

namespace globals {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;

	const int FPS = 60;
    const int frameDelay = 1000 / FPS;

	const float SPRITE_SCALE = 1.0f;
	const float SPAWNABLE_SCALE = 1.0f;

	const int maxSpawnables = 5;

	const int TREE_SPEED = 1;
	const int GRASS_SPEED = 2;
	const int ROAD_SPEED = 4;
	const int BUILDING_SPEED = 2;

	const std::vector<int> GRASS_IDX = { 12, 13, 20, 21, 65, 66 };
	const std::vector<int> TREE_IDX = { 31, 39, 77, 78, 93 };
	const std::vector<int> ROAD_IDX = { 11, 19 }; 
	const std::vector<int> BUILDINGS_IDX = { 50, 89, 15, 9 };
	const std::vector<int> STUDY_IDX = { 50 };
	const std::vector<int> FOOD_IDX = { 89 };
	const std::vector<int> HOSTEL_IDX = { 15 };
	const std::vector<int> SAC_IDX = { 9 };

	const float energyDecay = 0.0005;
	const float socialQuotientDecay = 0.0005;
	const float fitnessDecay = 0.0005;
	const float nerdinessDecay = 0.0005;

	const float energyGain = 0.002;
	const float hostelFoodCost = 0.005;
	const float outsideFoodCost = 0.01;

	const float nerdinessGain = 0.002;
	const float socialQuotientGain = 0.002;
	const float fitnessGain = 0.002;
	
	const int enemySpawnRate = 500;
	const int maxEnemies = 5;
	
	const int speedDampingFactor = 4;
	const int enemySpeed_ROAD = 2;
	const int enemySpeed_GRASS = 1;
	const int enemySpeed_TREE = 1;
}

#endif