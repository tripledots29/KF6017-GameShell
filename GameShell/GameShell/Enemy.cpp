#include "Enemy.h"
#include "gamecode.h"

Enemy::Enemy() :GameObject(ObjectType::ENEMY)
{
	objectActive = false;
	bmpRadius = 128.0f;
}

Enemy::~Enemy()
{

}


void Enemy::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	angle = 3.1420f / -2;
	objectActive = true;

	position = initialPosition;
	velocity = initialVelocity;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	canCollide = isCollidable;

	deltaBearing = (rand() % 100 - 400.0f) /200.0f;
	timeUntilAttack = (rand() % 100 + 30) / 10.0f;

	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"boss.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"boss1.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"boss2.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"boss3.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"boss4.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"boss5.bmp");

	chosenImage = rand() % 6;

}

void Enemy::Render()
{
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, images[int(chosenImage)], imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

void Enemy::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position, size); //circle around the enemy for easier hits

	bearingFromPlayer = bearingFromPlayer + deltaBearing * frameTime;

	timeUntilAttack = timeUntilAttack - frameTime;

	float rateOfChange = 0.99f * frameTime;

	//MyDrawEngine::GetInstance()->WriteDouble(500, 500, timeUntilAttack, MyDrawEngine::RED);

	if (timeUntilAttack >= 1 && pTarget)
	{
		targetPoint.setBearing(bearingFromPlayer, RADIUSFROMPLAYER);
		targetPoint.XValue += 1000;
		targetPoint = targetPoint + pTarget->getPosition();

		desiredVelocity = targetPoint - position;
		desiredVelocity = desiredVelocity.unitVector() * 1500.0f;

		if (rateOfChange > 1.0f)
		{
			rateOfChange = 1.0f;
		}

		velocity = desiredVelocity * rateOfChange + velocity * (1.0f - rateOfChange);
		angle = velocity.angle();

		//MyDrawEngine::GetInstance()->FillCircle(targetPoint, 5, MyDrawEngine::RED); //debug
	}

	
	else if ((timeUntilAttack < 1 && timeUntilAttack > 0) && (pTarget))
	{

		targetPoint.setBearing(bearingFromPlayer, 0);
		targetPoint = targetPoint + pTarget->getPosition();

		desiredVelocity = targetPoint - position;
		desiredVelocity = desiredVelocity.unitVector() * 200.0f;

		if (rateOfChange > 1.0f)
		{
			rateOfChange = 1.0f;
		}

		velocity = desiredVelocity * rateOfChange + velocity * (0.7f - rateOfChange);

		angle = velocity.angle();

		//MyDrawEngine::GetInstance()->FillCircle(targetPoint, 55, MyDrawEngine::RED); //debug

	}

	else
	{
		GameObject* pTheBullet = pTheObjectManager->Create(ObjectType::BULLET);

		//bullet's data
		Vector2D bulletVelocity;
		Vector2D bulletLaunchPosition;

		//setting bearings for where it comes from and how fast it goes
		bulletLaunchPosition.setBearing(angle, size * 1.5f);
		bulletVelocity.setBearing(angle, 1000.0f); //1000 magnitude for the bullet = fast shooting. and at angle ship is currently facing

		//initialise the bullet
		pTheBullet->Initialise(position + bulletLaunchPosition, bulletVelocity, 8.0f, false, true);

		timeUntilAttack = (rand() % 100 + 30) / 10.0f;
	}

	//calculating friction and momentum
	Vector2D friction = -1.0f * velocity;
	velocity = velocity + friction * frameTime;

	position = position + velocity * frameTime;

	invDelay = invDelay - frameTime; //every frame take away until delay hits 0

}

IShape2D& Enemy::GetShape()
{
	return collisionShape;
}

void Enemy::ProcessCollision(GameObject& collidedWith)
{
  	if ((typeid(collidedWith) == typeid(Bullet)) && (collidedWith.getBulletType() == true) && (invDelay < 0))
	{
		Game::instance.StopHit();

		if (pTheSoundFX)
		{
			pTheSoundFX->PlayExplosion();
		}
		TakeDamage(40);
		invDelay = INVDELAYDEFAULT;
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
		pTheExplosion->Initialise(position, Vector2D(0, 0), size, false, false);
	}

	if ((typeid(collidedWith) == typeid(Rock)) && invDelay < 0)
	{
		if (pTheSoundFX)
		{
			pTheSoundFX->PlayExplosion();
		}
		TakeDamage(10);
		invDelay = INVDELAYDEFAULT;
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
		pTheExplosion->Initialise(position, Vector2D(0, 0), size, false, false);
	}
}

void Enemy::SetTarget(Spaceship* pTheTarget)
{
	pTarget = pTheTarget;
}

void Enemy::TakeDamage(int amount)
{
	health = health - amount;

	Message m;
	m.type = EventType::ENEMY_HIT;
	m.location = position;
	m.pSource = this;
	m.otherData = int(health);
	pTheObjectManager->SendMessage(m);

	if (health <= 0)
	{
		Deactivate();
		Message m;
		m.type = EventType::ENEMY_DESTROYED;
		m.location = position;
		m.pSource = this;
		m.otherData = int(health);
		pTheObjectManager->SendMessage(m);
	}
}



void Enemy::HandleMessage(Message& msg)
{
	if (msg.type == EventType::PLAYER_DESTROYED && msg.pSource == pTarget)
	{
		pTarget = nullptr;
	}

	if (msg.type == EventType::PLAYER_SPAWNED)
	{
		pTarget = msg.pSource;
	}
}


