#include "Rock.h"
#include "Bullet.h"

Rock::Rock()
{
	objectActive = false;
	pTheObjectManager = 0;
	bmpRadius = 64.0f;
}

Rock::~Rock()
{

}


void Rock::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, ObjectManager* p_TheObjectManager)
{
	objectActive = true;
	position = initialPosition;
	velocity = initialVelocity;

	size = initialSize;
	imageScale = initialSize / bmpRadius;

	splittable = isSplittable;

	LoadImage(L"rock1.bmp");

	pTheObjectManager = p_TheObjectManager;
}

void Rock::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

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

void Rock::ProcessCollision(GameObject& collidedWith)
{
	if (typeid(collidedWith) == typeid(Bullet))
	{
		if (splittable == true)
		{
			Deactivate();
			for (int i = 0; i < 3; i++)
			{
				//create a new rock
				Rock* pRock = new Rock();

				//give it a position and velocity
				Vector2D pos = position + Vector2D(rand() % 250 - 75, rand() % 250 - 75);
				Vector2D vel(rand() % 200 + (-100), rand() % 200 + (-100));

				//initalise it
				pRock->Initialise(pos, vel, size/2, false, pTheObjectManager);

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
		}
	}
}