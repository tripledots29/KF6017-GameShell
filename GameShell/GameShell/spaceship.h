#pragma once
#include "GameObject.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "Rock.h"
#include "Explosion.h"

class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	const float shootDelayDefault = 0.2f;
	float shootDelay = shootDelayDefault;
	Circle2D collisionShape;



public:
	Spaceship();
	~Spaceship();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;


};
