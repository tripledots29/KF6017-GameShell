#include "Explosion.h"
//#include "SoundFX.h"

Explosion::Explosion() :GameObject(ObjectType::EXPLOSION)
{
	objectActive = false;
	bmpRadius = 32.0f;
}

Explosion::~Explosion()
{

}

void Explosion::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	objectActive = true;
	position = initialPosition;
	canCollide = isCollidable;
	velocity = initialVelocity;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	isJetStream = isSplittable;
	currentImage = 0.1f;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
}


void Explosion::Render() 
{
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

void Explosion::Update(float frameTime)
{

	if (currentImage < 7)
	{
		if (isJetStream)
		{
			currentImage = currentImage + frameTime * 80; //last a milisecond (80*frameTime) when 8 images. jet on back of spaceship
		}

		if (!isJetStream)
		{
			currentImage = currentImage + frameTime * 8; //last a second (8*frameTime) when 8 images
		}
	}


	else
	{
		Deactivate();
	}

	position = position + velocity * frameTime;

}


IShape2D& Explosion::GetShape()
{
	return collisionShape;
}