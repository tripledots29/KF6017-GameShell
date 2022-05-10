#pragma once
#include "vector2D.h"

class GameObject;

enum class EventType 
{
	LEVEL_START,
	PLAYER_HIT, PLAYER_DESTROYED, PLAYER_SPAWNED,
	EXPLOSION_OCCUR, ROCK_EXPLODE,
	ENEMY_HIT, ENEMY_DESTROYED
};

struct Message
{
	EventType type;
	Vector2D location;
	GameObject* pSource;
	int otherData;
};