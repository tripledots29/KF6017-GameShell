#pragma once
#include "GameObject.h"
#include "ObjectManager.h"


class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	const float SHOOTDELAYDEFAULT = 0.2f;
	const float INVDELAYDEFAULT = 0.5f;

	float shootDelay = SHOOTDELAYDEFAULT;
	float invDelay = INVDELAYDEFAULT;

	Circle2D collisionShape;

	float health;

public:
	Spaceship();
	~Spaceship();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
	void TakeDamage(int amount);

};
