#include "Bullet.h"
#include "SoundFX.h"

Bullet::Bullet() :GameObject(ObjectType::BULLET)
{
	objectActive = false;

	lifeTimer = 5.0f;
	bmpRadius = 4.0f;
}

Bullet::~Bullet()
{

}


void Bullet::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	objectActive = true;
	position = initialPosition;
	velocity = initialVelocity;
	size = initialSize;
	canCollide = isCollidable;
	splittable = isSplittable;
	imageScale = initialSize / bmpRadius;
	LoadImage(L"bullet.bmp");
	if (pTheSoundFX)
	{
		pTheSoundFX->PlayShot();
	}
}

void Bullet::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position.YValue + size,position.XValue - size, position.YValue - size, position.XValue + size); //exact square around the bullet

	position = position + velocity * frameTime;

	angle = velocity.angle();

	if (lifeTimer > 0)
	{
		lifeTimer = lifeTimer - frameTime; //timer is how long it takes in seconds for a bullet to "disappear" (become inactive)
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
	if ((typeid(collidedWith) == typeid(Bullet)) || ((typeid(collidedWith) == typeid(Spaceship)) && (collidedWith.getBulletType() == true)))
	{

	}

	else
	{
		Deactivate();
	}
}
