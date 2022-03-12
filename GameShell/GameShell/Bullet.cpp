#include "Bullet.h"

Bullet::Bullet()
{
	objectActive = false;
}

Bullet::~Bullet()
{

}

void Bullet::Intialise(Vector2D initialPosition, Vector2D initialVelocity)
{
	objectActive = true;
	timer = 2.0f;
	position = initialPosition;
	velocity = initialVelocity;
	LoadImage(L"bullet.bmp");
}

void Bullet::Update(float frameTime)
{

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