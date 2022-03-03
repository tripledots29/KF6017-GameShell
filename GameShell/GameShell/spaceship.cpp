#include "spaceship.h"

Spaceship::Spaceship()
{
	objectActive = false;
}

Spaceship::~Spaceship()
{

}


void Spaceship::Intialise(Vector2D initialPosition)
{
	objectActive = true;
	position = initialPosition;
	velocity.set (0,0);
	LoadImage(L"ship.bmp");
}


void Spaceship::Update(float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		Vector2D acceleration(300, 0);
		velocity = velocity + acceleration * frameTime;
	}

	if (pInputs->KeyPressed(DIK_LEFT))
	{
		Vector2D acceleration(-300, 0);
		velocity = velocity + acceleration * frameTime;
	}

	if (pInputs->KeyPressed(DIK_UP))
	{
		Vector2D acceleration(0, 300);
		velocity = velocity + acceleration * frameTime;
	}

	if (pInputs->KeyPressed(DIK_DOWN))
	{
		Vector2D acceleration(0, -300);
		velocity = velocity + acceleration * frameTime;
	}

	position = position + velocity * frameTime;


}
