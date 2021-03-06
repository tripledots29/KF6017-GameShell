#include "Rock.h"
#include "gamecode.h"

Rock::Rock() :GameObject(ObjectType::ROCK)
{
	objectActive = false;

	bmpRadius = 64.0f;
}

Rock::~Rock()
{

}


void Rock::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	angle = rand() % 628 / 100.0f;
	objectActive = true;
	position = initialPosition;
	velocity = initialVelocity;
	canCollide = isCollidable;

	size = initialSize;
	imageScale = initialSize / bmpRadius;

	splittable = isSplittable;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"rock1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"rock2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"rock3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"rock4.bmp");

	chosenImage = rand() % 4;

}

void Rock::Render()
{
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(chosenImage)], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

void Rock::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

	//update position based on velocity
	position = position + velocity * frameTime;

	float screenLeftLimit = MyDrawEngine::GetInstance()->GetViewport().GetBottomLeft().XValue - 500.0f; //furthest points objects can go off the screen

	if (position.XValue < screenLeftLimit)
	{
		Deactivate();
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
		Message m;
		m.type = EventType::ROCK_EXPLODE;
		m.location = position;
		m.pSource = this;
		m.otherData = int(size);
		pTheObjectManager->SendMessage(m);

		if (pTheSoundFX)
		{
			pTheSoundFX->PlayExplosion();
		}

		Game::instance.StopHit();

		if (splittable == true)
		{
			Deactivate();

			GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION); 
			pTheExplosion->Initialise(position, Vector2D(0,0), size, false, false);


			for (int i = 0; i < 3; i++)
			{
				//create a new rock
				GameObject* pRock = pTheObjectManager->Create(ObjectType::ROCK);

				//give it a position and velocity
				Vector2D pos = position + Vector2D(rand() % 250 - 75.0f, rand() % 250 - 75.0f);
				Vector2D vel(rand() % 200 + (-100.0f), rand() % 200 + (-100.0f));

				//initalise it
				pRock->Initialise(pos, vel, size/2, false, true);

				//if the object manager is there then add the new rocks to it
			}
		}

		else
		{
			Deactivate();

			GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
			pTheExplosion->Initialise(position, Vector2D(0, 0), size, false, false);
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