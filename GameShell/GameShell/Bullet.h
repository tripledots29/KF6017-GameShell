#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Bullets used by player and enemy to destruct game world and eachother
*
* @author W18010680
*/

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float lifeTimer;
	Rectangle2D collisionShape;

	PictureIndex images[2];

public:
	Bullet();
	~Bullet();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;
};
