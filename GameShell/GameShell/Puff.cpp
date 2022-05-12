#include "Puff.h"

Puff::Puff() :GameObject(ObjectType::PUFF)
{
	objectActive = false;
	bmpRadius = 32.0f;
}

Puff::~Puff()
{

}

void Puff::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	objectActive = true;
	position = initialPosition;
	canCollide = isCollidable;
	velocity = initialVelocity;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	currentImage = 0.1f;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"puff1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"puff2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"puff3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"puff4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"puff5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"puff6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"puff7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"puff8.bmp");
}


void Puff::Render()
{
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(currentImage)], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

void Puff::Update(float frameTime)
{

	if (currentImage < 7)
	{
		currentImage = currentImage + frameTime * 8; //last a milisecond (80*frameTime) when 8 images. jet on back of spaceship
	}

	else
	{
		Deactivate();
	}

	position = position + velocity * frameTime;

}


IShape2D& Puff::GetShape()
{
	return collisionShape;
}