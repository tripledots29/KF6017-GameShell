#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "Explosion.h"

class Rock : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	bool splittable;

public:
	Rock();
	~Rock();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;

};
