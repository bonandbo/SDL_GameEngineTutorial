#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D() : x(0.0f), y(0.0f) { };
	Vector2D(float _x, float _y) : x(_x), y(_y) { };
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