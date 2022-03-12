#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "Bullet.h"

class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	const float shootDelayDefault = 0.4f;
	float shootDelay = shootDelayDefault;
	ObjectManager* pTheObjectManager;

public:
	Spaceship();
	~Spaceship();
	void Intialise(Vector2D initialPosition, ObjectManager* p_TheObjectManager);
	void Update(float frameTime) override;
};
