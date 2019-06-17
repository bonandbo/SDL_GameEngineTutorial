#pragma once

#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* GetInstance(); // static keyword ?

	bool Circle(Character* char1, Character* char2);
	bool Box(Rect2D rect1, Rect2D rect2);
private:
	Collisions(); // why ?
	static Collisions* m_Instance;
};
