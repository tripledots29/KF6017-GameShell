#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Puff created to show damage
*
* @author W18010680
*/
class Puff : public GameObject
{
private:

	Vector2D velocity;
	PictureIndex images[8];
	float currentImage;
	Circle2D collisionShape;

public:
	Puff();
	~Puff();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	//void ProcessCollision(GameObject& collidedWith) override;

};
