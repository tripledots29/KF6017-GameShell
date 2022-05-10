#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Spaceship;

class Enemy : public GameObject
{
private:
	Vector2D velocity;

	Rectangle2D collisionShape;
	const float RADIUSFROMPLAYER = 650.0f;
	float bearingFromPlayer;
	float timeUntilAttack;
	float health = 100;
	float deltaBearing;

	Vector2D desiredVelocity;
	Vector2D targetPoint;

	GameObject* pTarget;

public:
	Enemy();
	~Enemy();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
	void SetTarget(Spaceship* pTarget);
	void TakeDamage(int amount);
	void HandleMessage(Message& msg) override;
};
