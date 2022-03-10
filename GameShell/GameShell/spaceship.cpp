#include "spaceship.h"

Spaceship::Spaceship()
{
	objectActive = false;
}

Spaceship::~Spaceship()
{

}


void Spaceship::Intialise(Vector2D initialPosition, ObjectManager* p_TheObjectManager)
{
	objectActive = true;
	position = initialPosition;
	velocity.set (0,0);
	LoadImage(L"ship.bmp");

	pTheObjectManager = p_TheObjectManager;
}


void Spaceship::Update(float frameTime)
{
	
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	//key inputs for movement
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

	if (pInputs->KeyPressed(DIK_Q))
	{
		angle = angle + 1.0f * frameTime;
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

	Vector2D friction = -0.5 * velocity;
	velocity = velocity + friction * frameTime;
	position = position + velocity * frameTime;

	//key inputs for shooting
	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		Bullet* pTheBullet = new Bullet();
		Vector2D bulletVelocity;
		bulletVelocity.setBearing(angle, 200.0f);
		pTheBullet->Intialise(position, bulletVelocity);
		if (pTheObjectManager)
		{
			pTheObjectManager->AddObject(pTheBullet);
		}
	}

}
