#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D() : x(0.0f), y(0.0f) { };
	Vector2D(float _x, float _y) : x(_x), y(_y) { };
};

struct Rect2D
{
	float x;
	float y;
	size_t w;
	size_t h;

	Rect2D() : x(0.0f), y(0.0f), w(0), h(0) {};
	Rect2D(float _x, float _y, size_t _w, size_t _h) : x(_x), y(_y), w(_w), h(_h) {};
};

enum SCENES
{
	INTRO = 0,
	MENU,
	LEVEL_1,
	LEVEL_2,
	GAMEOVER,
	HIGHSCORE
};


enum DIRECTION
{
	LEFT = 0,
	RIGHT
};