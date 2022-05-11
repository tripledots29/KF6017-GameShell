#include "Enemy.h"

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
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	canCollide = isCollidable;
	deltaBearing = (rand() % 100 - 450.0f) /300.0f;
	timeUntilAttack = rand() % 50 / 10.0f;
	velocity.set(0.0f, 0.0f);

	LoadImage(L"boss.bmp");
}

void Enemy::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position.YValue + size, position.XValue - size, position.YValue - size, position.XValue + size); //exact square around the enemy

	bearingFromPlayer = bearingFromPlayer + deltaBearing * frameTime;

	timeUntilAttack = timeUntilAttack - frameTime;

	float rateOfChange = 0.8f * frameTime;


	if (timeUntilAttack > 0 && pTarget)
	{
		targetPoint.setBearing(bearingFromPlayer, RADIUSFROMPLAYER-400);

		targetPoint = targetPoint + pTarget->getPosition();


		desiredVelocity = targetPoint - position;
		desiredVelocity = desiredVelocity.unitVector() * 1800.0f;

		if (rateOfChange > 1.0f)
		{
			rateOfChange = 1.0f;
		}

		velocity = desiredVelocity * rateOfChange + velocity * (1.0f - rateOfChange);
		angle = velocity.angle();

		MyDrawEngine::GetInstance()->FillCircle(targetPoint, 5, MyDrawEngine::RED); //debug
	}

	else if (pTarget)
	{
		desiredVelocity = desiredVelocity.unitVector() * 300.0f;

		velocity = desiredVelocity * rateOfChange + velocity * (1.0f - rateOfChange);
		angle = velocity.angle();

		targetPoint = targetPoint + pTarget->getPosition();
	

		if (velocity.magnitude() < 500.0f)
		{
			GameObject* pTheBullet = pTheObjectManager->Create(ObjectType::BULLET);

			//bullet's data
			Vector2D bulletVelocity;
			Vector2D bulletLaunchPosition;

			//setting bearings for where it comes from and how fast it goes
			bulletLaunchPosition.setBearing(pTarget->getAngle(), size * 1.5f);
			bulletVelocity.setBearing(angle, 1000.0f); //500 magnitude for the bullet = fast shooting. and at angle ship is currently facing

			//initialise the bullet
			//pTheBullet->Initialise(position + bulletLaunchPosition, bulletVelocity, 8.0f, false, true);

			timeUntilAttack = rand() % 100 / 10.0f;

		}

	}

	else
	{

	}

	//if (MyInputs::GetInstance()->KeyPressed(DIK_P))
	//{
	//	TakeDamage(100);
	//}

	position = position + velocity * frameTime;

	invDelay = invDelay - frameTime; //every frame take away until delay hits 0

}

IShape2D& Enemy::GetShape()
{
	return collisionShape;
}

void Enemy::ProcessCollision(GameObject& collidedWith)
{
  	if ((typeid(collidedWith) == typeid(Bullet)) && (collidedWith.getBulletType() == true))
	{
		TakeDamage(50);
		GameObject* pTheExplosion = pTheObjectManager->Create(ObjectType::EXPLOSION);
		pTheExplosion->Initialise(position, Vector2D(0, 0), size, false, false);
	}

	if ((typeid(collidedWith) == typeid(Rock)) && invDelay < 0)
	{
		TakeDamage(40);
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
