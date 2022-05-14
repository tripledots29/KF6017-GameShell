#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Enemy class with "AI". Moves around player then aims and shoots based on timer
*
* @author W18010680
*/

class Spaceship;

class Enemy : public GameObject
{
private:
	Vector2D velocity;

	PictureIndex images[6];
	int chosenImage;

	Circle2D collisionShape;
	const float RADIUSFROMPLAYER = 850.0f;
	float bearingFromPlayer;
	float timeUntilAttack;
	float health = 100;
	float deltaBearing;

	const float INVDELAYDEFAULT = 0.5f;
	float invDelay = INVDELAYDEFAULT;

	Vector2D desiredVelocity;
	Vector2D targetPoint;

	GameObject* pTarget;

public:
	Enemy();
	~Enemy();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
	void SetTarget(Spaceship* pTarget);
	void TakeDamage(int amount);
	void HandleMessage(Message& msg) override;
};
