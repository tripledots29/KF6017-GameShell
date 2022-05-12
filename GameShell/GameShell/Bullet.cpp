#include "Bullet.h"
//#include "SoundFX.h"

Bullet::Bullet() :GameObject(ObjectType::BULLET)
{
	objectActive = false;

	lifeTimer = 2.5f;
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
	imageScale = initialSize / bmpRadius;	
	
	canCollide = isCollidable;
	splittable = isSplittable;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"bullet.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"plasma.bmp");

	if (pTheSoundFX && splittable == true)
	{
		pTheSoundFX->PlayShot();
	}

	if (pTheSoundFX && splittable == false)
	{
		pTheSoundFX->PlayLaunch();
	}


}

void Bullet::Render()
{
	if (objectActive && splittable == true) //true = player
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[0], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}

	if (objectActive && splittable == false) //false = enemy
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[1], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
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
	if (!
		((typeid(collidedWith) == typeid(Bullet)) || 
		((typeid(collidedWith) == typeid(Enemy)) && (collidedWith.getBulletType() == false)) || 
		((typeid(collidedWith) == typeid(Spaceship)) && (collidedWith.getBulletType() == true))))
	{
		Deactivate();
	}
}
