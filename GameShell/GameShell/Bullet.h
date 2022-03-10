#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float timer;

public:
	Bullet();
	~Bullet();
	void Intialise(Vector2D initialPosition, Vector2D initialVelocity);
	void Update(float frameTime) override;
};
