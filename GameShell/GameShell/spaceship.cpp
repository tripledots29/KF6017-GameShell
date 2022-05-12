#include "spaceship.h"
//#include "SoundFX.h"

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
	m.otherData = int(health);
	pTheObjectManager->SendMessage(m);

}

void Spaceship::Render()
{
	if (invDelay > 0 && objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, pic, imageScale, angle, 0.5f); //show invulnerability by fading
	}

	else if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, pic, imageScale, angle);
	}
}

void Spaceship::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size);

	//referencing the inputs
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	//setting acceleration
	Vector2D acceleration;
	acceleration.setBearing(angle, 200.0f);


	//key inputs for movement
	if ((pInputs->KeyPressed(DIK_RIGHT)) || (pInputs->KeyPressed(DIK_D)))
	{
		acceleration.setBearing(angle, 500.0f);
		if (pTheSoundFX)
		{
			pTheSoundFX->SetEngineVolume(20);
			pTheSoundFX->StartPlayingEngineSound();
		}
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
		Vector2D jet;
		jet.setBearing(angle + 3.14f, 36.0f);
		jet = jet + position;
		Vector2D jetVel;
		jetVel.setBearing(angle + 3.14f, 500.0f);
		jetVel = jetVel + velocity;
		pTheExplosion->Initialise(jet, jetVel, 15.0f, true, false);
	}
	else
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->StopPlayingEngineSound();
		}
	}
	
	if ((pInputs->KeyPressed(DIK_LEFT)) || (pInputs->KeyPressed(DIK_A)))
	{
		acceleration.setBearing(angle, 100.0f);

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
	Vector2D friction = -1.0f * velocity;
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
		bulletLaunchPosition.setBearing(angle, size*2.5f);
		bulletVelocity.setBearing(angle, 1000.0f); //500 magnitude for the bullet = fast shooting. and at angle ship is currently facing

		//initialise the bullet
		pTheBullet->Initialise(position+bulletLaunchPosition, bulletVelocity, 16.0f, true, true);

		shootDelay = SHOOTDELAYDEFAULT; //reset shootDelay back to default value. value = how many seconds a bullet replenishes
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
	
	//camera moves when player does
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D((position.XValue+700), 0));


	invDelay = invDelay - frameTime; //every frame take away until delay hits 0

	if (health < 55 && health > 25)
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->SetAlertVolume(40);
			pTheSoundFX->StartPlayingAlertSound();
			if (rand() % 1000 < PUFFCHANCE)
			{
				GameObject* pThePuff = pTheObjectManager->Create(ObjectType::PUFF);
				Vector2D offset;
				offset.setBearing(angle + 1.57f, 5);
				offset += position;
				pThePuff->Initialise(offset, Vector2D(0, 0), size / 3, false, false);
			}
		}
	}
	
	else if (health <= 25)
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->SetAlertVolume(80);
			pTheSoundFX->StartPlayingAlertSound();
			if (rand() % 500 < PUFFCHANCE)
			{
				GameObject* pThePuff = pTheObjectManager->Create(ObjectType::PUFF);
				Vector2D offset;
				offset.setBearing(angle + 1.57f, 5);
				offset += position;
				pThePuff->Initialise(offset, Vector2D(0, 0), size / 2, false, false);
			}
			if (rand() % 2000 < PUFFCHANCE)
			{
				GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
				Vector2D offset;
				offset.setBearing(angle + 1.57f, -5);
				offset += position;
				pTheExplosion->Initialise(offset, Vector2D(0, 0), size / 1.5f, false, false);
			}
		}
	}

	else
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->StopPlayingAlertSound();
		}
	}

}

void Spaceship::TakeDamage(int amount)
{
	health = health - amount;

	Message m;
	m.type = EventType::PLAYER_HIT;
	m.location = position;
	m.pSource = this;
	m.otherData = int(health);
	pTheObjectManager->SendMessage(m);

	if (health <= 0)
	{
		Deactivate();
		Message m;
		m.type = EventType::PLAYER_DESTROYED;
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

		invDelay = INVDELAYDEFAULT;
		TakeDamage(int(collidedWith.GetSize()/5));
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION); 
		pTheExplosion->Initialise(position, Vector2D(0,0), size, false, false);
	}

	if ((typeid(collidedWith) == typeid(Bullet)) && (collidedWith.getBulletType() == false))
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->PlayExplosion();
		}
		TakeDamage(20);
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
		pTheExplosion->Initialise(position, Vector2D(0, 0), size/2, false, false);
	}


}

