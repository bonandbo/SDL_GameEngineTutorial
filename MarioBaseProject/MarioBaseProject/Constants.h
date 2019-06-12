#pragma once

// Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

/* Other way in C++11
constexpr int SCREEN_WIDTH 512
constexpr int SCREEN_HEIGHT 416
*/


#define LOG(...) { printf(__VA_ARGS__); printf("\n"); }
