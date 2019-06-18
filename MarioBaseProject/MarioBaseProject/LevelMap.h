#pragma once

#include "Commons.h"
#include "Constants.h"

class LevelMap
{
public:
	LevelMap();
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int getTileAt(size_t x, size_t y);
private:
	int** m_Map;
};