#pragma once
#include "vector2D.h"

class GameObject;

enum class EventType { OBJECT_DESTROYED, EXPLOSION_OCCUR, BULLET_FIRED, LEVEL_START, ROCK_EXPLODE, SPACESHIP_HIT };

struct Message
{
	EventType type;
	Vector2D location;
	GameObject* pSource;
	int otherData;
};