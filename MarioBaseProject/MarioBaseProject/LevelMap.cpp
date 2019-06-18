#include "LevelMap.h"


LevelMap::LevelMap()
{
	m_Map = nullptr;
}

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	// alloc mem
	m_Map = new int*[MAP_HEIGHT];
	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		m_Map[i] = new int[MAP_WIDTH];
	}

	// assign value to map
	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		for (size_t j = 0; j < MAP_WIDTH; j++)
		{
			m_Map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_Map[i];
	}
	delete[] m_Map;
}

int LevelMap::getTileAt(size_t x, size_t y)
{
	if (x < MAP_HEIGHT && y < MAP_WIDTH)
		return m_Map[x][y];

	return 0;
}
