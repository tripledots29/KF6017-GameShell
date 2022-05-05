#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Enemy : public GameObject
{
private:
	Vector2D velocity;

	Rectangle2D collisionShape;

	float health = 100;


public:
	Enemy();
	~Enemy();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;

};
