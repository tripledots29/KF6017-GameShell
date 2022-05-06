#include "spaceship.h"
#include "SoundFX.h"

Spaceship::Spaceship():GameObject(ObjectType::SPACESHIP)
{
	objectActive = false;

	bmpRadius = 32.0f;

	//type = ObjectType::SPACESHIP;
}

Spaceship::~Spaceship()
{

}

const float MAXDEVIATION = 1.5f;

void Spaceship::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	angle = 3.1420f / 2 ;
	objectActive = true;
	position = initialPosition;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	canCollide = isCollidable;
	health = 100;
	velocity.set (0.0f,0.0f);
	LoadImage(L"ship.bmp");


	Message m;
	m.type = EventType::PLAYER_SPAWNED;
	m.location = position;
	m.pSource = this;
	m.otherData = health;
	pTheObjectManager->SendMessage(m);

}


void Spaceship::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

	//referencing the inputs
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	Vector2D acceleration;
	acceleration.setBearing(angle, 300.0f);

	//key inputs for movement
	if ((pInputs->KeyPressed(DIK_RIGHT)) || (pInputs->KeyPressed(DIK_D)))
	{
		acceleration.setBearing(angle, 500.0f);
		if (pTheSoundFX)
		{
			pTheSoundFX->StartPlayingEngineSound();
		}
	}
	
	if ((pInputs->KeyPressed(DIK_LEFT)) || (pInputs->KeyPressed(DIK_A)))
	{
		acceleration.setBearing(angle, 100.0f);
		if (pTheSoundFX)
		{
			pTheSoundFX->StopPlayingEngineSound();
		}
	}
	
	velocity = velocity + acceleration * frameTime;

	//key inputs for rotating
	if ((pInputs->KeyPressed(DIK_UP)) || (pInputs->KeyPressed(DIK_W)))
	{
		angle = angle - MAXDEVIATION * frameTime;
	}

	if ((pInputs->KeyPressed(DIK_DOWN)) || (pInputs->KeyPressed(DIK_S)))
	{
		angle = angle + MAXDEVIATION * frameTime;
	}

	angle = angle - (angle - 3.14f / 2) * MAXDEVIATION * frameTime; 

	//calculating friction and momentum
	Vector2D friction = -0.5f * velocity;
	velocity = velocity + friction * frameTime;

	//updating position based on velocity + friction
	position = position + velocity * frameTime;

	//key inputs for shooting and shoot delays
	if ((pInputs->KeyPressed(DIK_SPACE)) && (shootDelay < 0))
	{
	
		GameObject* pTheBullet = pTheObjectManager->Create(ObjectType::BULLET);

		//bullet's data
		Vector2D bulletVelocity;
		Vector2D bulletLaunchPosition;

		//setting bearings for where it comes from and how fast it goes
		bulletLaunchPosition.setBearing(angle, size*1.5f);
		bulletVelocity.setBearing(angle, 1000.0f); //500 magnitude for the bullet = fast shooting. and at angle ship is currently facing

		//initialise the bullet
		pTheBullet->Initialise(position+bulletLaunchPosition, bulletVelocity, 4.0f, false, true);

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
	
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D((position.XValue+500), 0));


	invDelay = invDelay - frameTime; //every frame take away until delay hits 0

}

void Spaceship::TakeDamage(int amount)
{
	health = health - amount;

	Message m;
	m.type = EventType::SPACESHIP_HIT;
	m.location = position;
	m.pSource = this;
	m.otherData = int(health);
	pTheObjectManager->SendMessage(m);

	if (health <= 0)
	{
		Deactivate();
		Message m;
		m.type = EventType::OBJECT_DESTROYED;
		m.location = position;
		m.pSource = this;
		m.otherData = int(health);
		pTheObjectManager->SendMessage(m);
	}
}

IShape2D& Spaceship::GetShape()
{
	return collisionShape;
}

void Spaceship::ProcessCollision(GameObject& collidedWith)
{
	if (typeid(collidedWith) == typeid(Rock) && invDelay < 0)
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->PlayExplosion();
		}

		invDelay = invDelayDefault;
		TakeDamage(int(collidedWith.GetSize()/5));
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION); 
		pTheExplosion->Initialise(position, Vector2D(0,0), size, false, false);
	}

}

