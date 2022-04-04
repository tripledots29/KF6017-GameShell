#include "Rock.h"
#include "Bullet.h"

Rock::Rock()
{
	objectActive = false;

	bmpRadius = 64.0f;
}

Rock::~Rock()
{

}


void Rock::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	objectActive = true;
	position = initialPosition;
	velocity = initialVelocity;
	canCollide = isCollidable;
	size = initialSize;
	imageScale = initialSize / bmpRadius;

	splittable = isSplittable;

	LoadImage(L"rock1.bmp");

}

void Rock::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

	//update position based on velocity
	position = position + velocity * frameTime;


	//wrap around
	
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

void Rock::ProcessCollision(GameObject& collidedWith)
{
	if (typeid(collidedWith) == typeid(Bullet))
	{
		if (splittable == true)
		{
			Deactivate();

			Explosion* pTheExplosion = new Explosion();
			pTheExplosion->Initialise(position, Vector2D(0,0), size, false, false);
			pTheObjectManager->AddObject(pTheExplosion);


			for (int i = 0; i < 3; i++)
			{
				//create a new rock
				Rock* pRock = new Rock();

				//give it a position and velocity
				Vector2D pos = position + Vector2D(rand() % 250 - 75, rand() % 250 - 75);
				Vector2D vel(rand() % 200 + (-100), rand() % 200 + (-100));

				//initalise it
				pRock->Initialise(pos, vel, size/2, false, true);

				//if the object manager is there then add the new rocks to it
				if (pTheObjectManager)
				{
					pTheObjectManager->AddObject(pRock);
				}
			}
		}

		else
		{
			Deactivate();

			Explosion* pTheExplosion = new Explosion();
			pTheExplosion->Initialise(position, Vector2D(0, 0), size, false, false);
			pTheObjectManager->AddObject(pTheExplosion);
		}
	}

	if (typeid(collidedWith) == typeid(Rock))
	{
		Vector2D normal = (position - collidedWith.getPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = 0.8f * velocity;
		}
	}
}