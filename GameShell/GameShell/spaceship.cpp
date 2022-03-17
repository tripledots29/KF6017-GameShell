#include "spaceship.h"

Spaceship::Spaceship()
{
	objectActive = false;
}

Spaceship::~Spaceship()
{

}

const float Spaceship::RADIUS = 32.0f;

void Spaceship::Intialise(Vector2D initialPosition, ObjectManager* p_TheObjectManager)
{
	objectActive = true;
	position = initialPosition;
	velocity.set (0.0f,0.0f);
	LoadImage(L"ship.bmp");

	pTheObjectManager = p_TheObjectManager;
}


void Spaceship::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, 30);


	//referencing the inputs
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	//key inputs for movement
	if ((pInputs->KeyPressed(DIK_UP)) || (pInputs->KeyPressed(DIK_W)))
	{
		Vector2D acceleration;
		acceleration.setBearing(angle, 500.0f);
		velocity = velocity + acceleration * frameTime;
	}

	if ((pInputs->KeyPressed(DIK_DOWN)) || (pInputs->KeyPressed(DIK_S)))
	{
		Vector2D acceleration;
		acceleration.setBearing(angle, -500.0f);
		velocity = velocity + acceleration * frameTime;
	}

	//key inputs for rotating
	if ((pInputs->KeyPressed(DIK_LEFT)) || (pInputs->KeyPressed(DIK_A)))
	{
		angle = angle - 2.0f * frameTime;
	}

	if ((pInputs->KeyPressed(DIK_RIGHT)) || (pInputs->KeyPressed(DIK_D)))
	{
		angle = angle + 2.0f * frameTime;
	}

	//calculating friction and momentum
	Vector2D friction = -0.5 * velocity;
	velocity = velocity + friction * frameTime;

	//updating position based on velocity + friction
	position = position + velocity * frameTime;

	//key inputs for shooting and shoot delays
	if ((pInputs->KeyPressed(DIK_SPACE)) && (shootDelay < 0))
	{
		Bullet* pTheBullet = new Bullet();
		Vector2D bulletVelocity;
		Vector2D bulletLaunchPosition;
		bulletLaunchPosition.setBearing(angle, 200);
		bulletVelocity.setBearing(angle, 500.0f); //500 magnitude for the bullet = fast shooting. and at angle ship is currently facing
		pTheBullet->Intialise(position+bulletLaunchPosition, bulletVelocity);
		if (pTheObjectManager)
		{
			pTheObjectManager->AddObject(pTheBullet);
		}
		shootDelay = shootDelayDefault; //reset shootDelay back to default value. value = how many seconds a bullet replenishes
	}
	shootDelay = shootDelay - frameTime; //every frame take away until delay hits 0

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

IShape2D& Spaceship::GetShape()
{
	return collisionShape;
}

void Spaceship::ProcessCollision(GameObject* collidedWith)
{
	

}
