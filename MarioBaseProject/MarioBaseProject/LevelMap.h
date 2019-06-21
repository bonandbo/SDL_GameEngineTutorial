#pragma once

#include "Commons.h"
#include "Constants.h"

class LevelMap
{
public:
	LevelMap();
	LevelMap(std::string path);
	~LevelMap();

	int GetTileAt(size_t x, size_t y);
	void ChangeTileAt(size_t row, size_t column, size_t newValue);
	void LoadFromFile(std::string file);
private:
	int** m_Map;
	int m_Width;
	int m_Height;
};