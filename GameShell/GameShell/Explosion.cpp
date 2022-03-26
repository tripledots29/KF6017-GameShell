#include "Explosion.h"

Explosion::Explosion()
{
	objectActive = false;
}

Explosion::~Explosion()
{

}

void Explosion::Initialise(Vector2D initialPosition)
{
	objectActive = true;
	position = initialPosition;
	//images[0] = LoadImage(L"explosion1.bmp");
	//LoadImage(L"explosion2.bmp");
	//LoadImage(L"explosion3.bmp");
	//LoadImage(L"explosion4.bmp");
	//LoadImage(L"explosion5.bmp");
	//LoadImage(L"explosion6.bmp");
	//LoadImage(L"explosion7.bmp");
	//LoadImage(L"explosion8.bmp");
	PlaySound(L"explosion.wav");
}

/*
void Explosion::Render()
{

}
*/

