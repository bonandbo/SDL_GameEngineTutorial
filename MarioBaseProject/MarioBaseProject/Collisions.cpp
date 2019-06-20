#include "Collisions.h"
#include "Character.h"

// Init instance as null
Collisions* Collisions::m_Instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	if (m_Instance)
	{
		m_Instance = nullptr;
	}
}

Collisions* Collisions::GetInstance()
{
	// lazy init
	if (!m_Instance)
	{
		m_Instance = new Collisions;
	}
	return m_Instance;
}

bool Collisions::Circle(Character* char1, Character* char2)
{
	// vector between 2 point
	Vector2D vec = Vector2D(char1->GetPosition().x - char2->GetPosition().x, char1->GetPosition().y - char2->GetPosition().y);

	// length of vector
	double distance = sqrt(vec.x * vec.x + vec.y * vec.y);

	// Get collision radius of each character and calculate the distance
	double combinedDistance = (char1->GetCollisionRadius() + char2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Circle(Circle2D circle1, Circle2D circle2)
{
	bool isCollide = false;

	// vector connect 2 center
	Vector2D vec = Vector2D(circle1.x - circle2.x, circle1.y - circle2.y);

	// length of vector
	double distance = sqrt(vec.x * vec.x + vec.y * vec.y);

	// length of 2 radius
	double radiusDistance = circle1.r + circle1.r;

	return distance < radiusDistance;

	return isCollide;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	float leftA, leftB, rightA, rightB, topA, topB, botA, botB;

	// calculate side rect1
	leftA = rect1.x;
	rightA = rect1.x + rect1.w;
	topA = rect1.y;
	botA = rect1.y + rect1.h;

	// calculate side rect2
	leftB = rect2.x;
	rightB = rect2.x + rect2.w;
	topB = rect2.y;
	botB = rect2.y + rect2.h;

	// Check collide
	if (botA <= topB)
	{
		return false;
	}
	if (topA >= botB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	// none of them => true
	return true;


	//if (rect1.x + (rect1.w) > rect2.x
	//	&&	rect1.x + (rect1.w) < rect2.x + rect2.w
	//	&&	rect1.y + (rect1.h) > rect2.y
	//	&&	rect1.y + (rect1.h) > rect2.y + rect2.h)
	//{
	//	return true;
	//}
	//return false;
}
