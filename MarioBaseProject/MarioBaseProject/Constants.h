#pragma once

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

/* Other way in C++11
constexpr int SCREEN_WIDTH 512
constexpr int SCREEN_HEIGHT 416
*/


#ifdef DEBUG
#define LOG(...) { printf(__VA_ARGS__); printf("\n"); }
//#define DEBUG_RENDER
#else
#define LOG(...)
#endif

#define FOLDER_IMG "Images"

#define BACKGROUND_IMG "BackgroundMB.png"
#define TEST_IMG "test image.bmp"
#define COIN_IMG "Coin.png"
#define KOOPA_IMG "Koopa.png"
#define LUIGI_IMG "Luigi.png"
#define MARIO_IMG "Mario.png"
#define POWBLOCK_IMG "PowBlock.png"

#define MOVEMENT_SPD 200.0f
#define GRAVITY 400.0f
#define JUMP_FORCE 400.0f

#define INITIAL_POS_MARIO_Y 340.0f
#define INITIAL_COLLISION_RAIDUS 15.0f

#define MAP_WIDTH 16
#define MAP_HEIGHT 13

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define NUMBER_HIT_LEFT 3

#define INJURED_TIME 2.5f

#define MAP_1_BOTTOM_ROW 300.0f
#define KOOPA_SPEED 96.0f