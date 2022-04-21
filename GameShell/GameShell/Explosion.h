#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Explosion : public GameObject
{
private:

	PictureIndex images[8];
	float currentImage;
	Circle2D collisionShape;

public:
	Explosion();
	~Explosion();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	//void ProcessCollision(GameObject& collidedWith) override;

};
