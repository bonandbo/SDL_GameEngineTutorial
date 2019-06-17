#pragma once

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

/* Other way in C++11
constexpr int SCREEN_WIDTH 512
constexpr int SCREEN_HEIGHT 416
*/


#define LOG(...) { printf(__VA_ARGS__); printf("\n"); }

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
#define JUMP_FORCE 300.0f

#define INITIAL_POS_MARIO_Y 340.0f
#define INITIAL_COLLISION_RAIDUS 15.0f
