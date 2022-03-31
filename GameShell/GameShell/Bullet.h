#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float lifeTimer;
	Rectangle2D collisionShape;

public:
	Bullet();
	~Bullet();
	void Initialise(Vector2D initialPosition, float initialSize, Vector2D initialVelocity, bool isCollidable);
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
};
