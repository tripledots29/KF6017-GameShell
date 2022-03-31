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

	ObjectManager* pTheObjectManager;


public:
	Spaceship();
	~Spaceship();
	void Initialise(Vector2D initialPosition, float initialSize, bool isCollidable, ObjectManager* p_TheObjectManager);
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;


};
