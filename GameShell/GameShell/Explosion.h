#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Explosion : public GameObject
{
private:
	//Vector2D velocity;
	//Circle2D collisionShape;
	//PictureIndex images[8];
	//PictureIndex currentImage;

public:
	Explosion();
	~Explosion();
	void Intialise(Vector2D initialPosition);
	//void Update(float frameTime) override;
	//IShape2D& GetShape() override;
	//void ProcessCollision(GameObject* collidedWith) override;

};
