#include "LevelMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


LevelMap::LevelMap()
{
	m_Map = nullptr;
	m_Width = 0;
	m_Height = 0;
}

LevelMap::LevelMap(std::string path)
{
	// assign value to map
	LoadFromFile(path);
}

LevelMap::~LevelMap()
{
	for (int i = 0; i < m_Height; i++)
	{
		delete[] m_Map[i];
	}
	delete[] m_Map;
}

void LevelMap::LoadFromFile(std::string filePath) // if using C code will be faster 4-5 times
{
	std::ifstream file(filePath);
	std::string line;
	
	// get the first line
	std::getline(file, line);
	std::istringstream ss(line);
	ss >> m_Height >> m_Width;

	// alloc mem
	m_Map = new int*[m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		m_Map[i] = new int[m_Width];
	}

	// assign
	for (int i = 0; i < m_Height; i++)
	{
		// get all the rest
		std::getline(file, line);
		ss = std::istringstream(line);
		for (int j = 0; j < m_Width; j++)
		{
			ss >> m_Map[i][j];
		}
	}
}

int LevelMap::GetTileAt(size_t x, size_t y)
{
	if (x < MAP_HEIGHT && y < MAP_WIDTH)
		return m_Map[x][y];

	return 0;
}

void LevelMap::ChangeTileAt(size_t row, size_t column, size_t newValue)
{
	if(row < MAP_HEIGHT && column < MAP_WIDTH)
		m_Map[row][column] = newValue;
}
