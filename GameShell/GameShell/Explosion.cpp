#include "Explosion.h"

Explosion::Explosion()
{
	objectActive = false;
	bmpRadius = 32.0f;
}

Explosion::~Explosion()
{

}

void Explosion::Initialise(Vector2D initialPosition, bool isCollidable, float initialSize)
{
	objectActive = true;
	position = initialPosition;
	canCollide = isCollidable;
	size = initialSize;
	imageScale = initialSize / bmpRadius;

	currentImage = 0;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");

	PlaySound(L"explosion.wav");
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
		currentImage = currentImage + frameTime*8; //last a second (8*frameTime) when 8 images
	}

	else
	{
		Deactivate();
	}
}


IShape2D& Explosion::GetShape()
{
	return collisionShape;
}