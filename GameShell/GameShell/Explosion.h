#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

/*
* Purpose: Explosions created usually on impact, also used for jet stream.
* Desired effect based on time time taken for animation
*
* @author W18010680
*/
class Explosion : public GameObject
{
private:

	Vector2D velocity;
	PictureIndex images[8];
	float currentImage;
	Circle2D collisionShape;
	bool isJetStream;

public:
	Explosion();
	~Explosion();
	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	//void ProcessCollision(GameObject& collidedWith) override;

};
