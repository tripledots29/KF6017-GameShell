#include "spaceship.h"

Spaceship::Spaceship()
{
	objectActive = false;

	bmpRadius = 32.0f;

	//type = ObjectType::SPACESHIP;
}

Spaceship::~Spaceship()
{

}

void Spaceship::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	objectActive = true;
	position = initialPosition;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	canCollide = isCollidable;
	velocity.set (0.0f,0.0f);
	LoadImage(L"ship.bmp");

}


void Spaceship::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

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
	Vector2D friction = -0.5f * velocity;
	velocity = velocity + friction * frameTime;

	//updating position based on velocity + friction
	position = position + velocity * frameTime;

	//key inputs for shooting and shoot delays
	if ((pInputs->KeyPressed(DIK_SPACE)) && (shootDelay < 0))
	{
		//create a new rock
		//Bullet* pTheBullet = new Bullet();
		
		GameObject* pTheBullet = TheObjectManager.Create(L"Bullet");

		//bullet's data
		Vector2D bulletVelocity;
		Vector2D bulletLaunchPosition;

		//setting bearings for where it comes from and how fast it goes
		bulletLaunchPosition.setBearing(angle, size*1.5f);
		bulletVelocity.setBearing(angle, 500.0f); //500 magnitude for the bullet = fast shooting. and at angle ship is currently facing

		//initialise the bullet
		pTheBullet->Initialise(position+bulletLaunchPosition, bulletVelocity, 4.0f, false, true);

		// add the bullet to object manager
		//pTheObjectManager->AddObject(pTheBullet);

		shootDelay = shootDelayDefault; //reset shootDelay back to default value. value = how many seconds a bullet replenishes
	}
	shootDelay = shootDelay - frameTime; //every frame take away until delay hits 0

	//wrap around
	
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

void Spaceship::ProcessCollision(GameObject& collidedWith)
{
	if (typeid(collidedWith) == typeid(Rock))
	{
		Deactivate(); // if the spaceship crashes into asteroid then it dies

		//Explosion* pTheExplosion = new Explosion();
		//pTheExplosion->Initialise(position, false, size);
		//pTheObjectManager->AddObject(pTheExplosion);
	}
}

