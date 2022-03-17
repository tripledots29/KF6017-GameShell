#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float timer;
	Circle2D collisionShape;


public:
	Bullet();
	~Bullet();
	void Intialise(Vector2D initialPosition, Vector2D initialVelocity);
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject* collidedWith) override;
};
