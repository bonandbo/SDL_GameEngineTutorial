#pragma once

#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* GetInstance(); // static keyword ?

	bool Circle(Character* char1, Character* char2);
	bool Circle(Circle2D circle1, Circle2D circle2);
	bool Box(Rect2D rect1, Rect2D rect2);

	//@TODO:
	// To implement per-pixel collision
	// To implement the Circle collide with Box
private:
	Collisions(); // why ?
	static Collisions* m_Instance;
};
