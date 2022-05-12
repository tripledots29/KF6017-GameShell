#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Spaceship is the main player class that is controlled using the keyboard
* 
* @author W18010680
*/

class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	const float SHOOTDELAYDEFAULT = 0.2f;
	const float INVDELAYDEFAULT = 1.0f;

	float shootDelay = SHOOTDELAYDEFAULT;
	float invDelay = INVDELAYDEFAULT;

	Circle2D collisionShape;

	float health;

	const int PUFFCHANCE = 50;

public:
	Spaceship();
	~Spaceship();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
	void TakeDamage(int amount);

};
