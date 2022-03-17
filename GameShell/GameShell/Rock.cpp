#include "Rock.h"

Rock::Rock()
{
	objectActive = false;
}

Rock::~Rock()
{

}

void Rock::Intialise(Vector2D initialPosition)
{
	objectActive = true;
	position = initialPosition;
	velocity.set(rand() % 200 + (-100), rand() % 200 + (-100));
	LoadImage(L"rock1.bmp");
}

void Rock::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, 30);

	//update position based on velocity
	position = position + velocity * frameTime;


	//wrap around
	if (position.XValue > 1800.0f) //horizontal size is -1800-1800
	{
		position.XValue = -1800.0f;
	}
	if (position.XValue < -1800.0f) //horizontal size is -1800-1800
	{
		position.XValue = 1800.0f;
	}
	if (position.YValue > 1000.0f) //vertical size is -1000-1000
	{
		position.YValue = -1000.0f;
	}
	if (position.YValue < -1000.0f) //vertical size is -1000-1000
	{
		position.YValue = 1000.0f;
	}




}


IShape2D& Rock::GetShape()
{
	return collisionShape;
}

void Rock::ProcessCollision(GameObject* collidedWith)
{

}