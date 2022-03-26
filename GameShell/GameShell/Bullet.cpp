#include "Bullet.h"

Bullet::Bullet()
{
	objectActive = false;
	timer = 2.0f;
	bmpRadius = 4.0f;
}

Bullet::~Bullet()
{

}


void Bullet::Initialise(Vector2D initialPosition, float initialSize, Vector2D initialVelocity)
{
	objectActive = true;
	position = initialPosition;
	velocity = initialVelocity;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	LoadImage(L"bullet.bmp");
	PlaySound(L"shoot.wav");
}

void Bullet::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position.YValue + size,position.XValue - size, position.YValue - size, position.XValue + size); //exact square around the bullet

	position = position + velocity * frameTime;

	if (timer > 0)
	{
		timer = timer - frameTime; //timer is how long it takes in seconds for a bullet to "disappear" (become inactive)
	}
	else
	{
		Deactivate();
	}

}


IShape2D& Bullet::GetShape()
{
	return collisionShape;
}


void Bullet::ProcessCollision(GameObject& collidedWith)
{
	Deactivate();
}
