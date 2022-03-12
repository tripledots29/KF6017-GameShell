#include "Rock.h"

Rock::Rock()
{
	objectActive = false;
}

Rock::~Rock()
{

}

void Rock::Intialise(Vector2D initialPosition)
{
	objectActive = true;
	position = initialPosition;
	velocity.set(40, 0);
	LoadImage(L"rock1.bmp");
}

void Rock::Update(float frameTime)
{
	position = position + velocity * frameTime;
}