#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Rock is an entity that can cause harm and annoyance to the player
*
* @author W18010680
*/

class Rock : public GameObject
{
private:
	Vector2D velocity;
	Circle2D collisionShape;
	PictureIndex images[4];
	int chosenImage;

public:
	Rock();
	~Rock();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void ProcessCollision(GameObject& collidedWith) override;

};
