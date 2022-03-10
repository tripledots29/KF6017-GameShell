#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;

public:
	Rock();
	~Rock();
	void Intialise(Vector2D initialPosition);
	void Update(float frameTime) override;
};