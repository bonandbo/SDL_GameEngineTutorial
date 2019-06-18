#pragma once

#include "Commons.h"
#include "Constants.h"

class LevelMap
{
public:
	LevelMap();
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(size_t x, size_t y);
	void ChangeTileAt(size_t row, size_t column, size_t newValue);
private:
	int** m_Map;
};