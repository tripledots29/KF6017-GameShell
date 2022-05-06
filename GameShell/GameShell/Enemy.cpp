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
	angle = 3.1420f / 2;
	objectActive = true;
	position = initialPosition;
	size = initialSize;
	imageScale = initialSize / bmpRadius;
	canCollide = isCollidable;
	deltaBearing = (rand() % 100 - 150.0f) /100.0f;
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
		targetPoint.setBearing(bearingFromPlayer, RADIUSFROMPLAYER);

		targetPoint = targetPoint + pTarget->getPosition();


		desiredVelocity = targetPoint - position;
		desiredVelocity = desiredVelocity.unitVector() * 700.0f;

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
		desiredVelocity = desiredVelocity.unitVector() * 400.0f;

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
			pTheBullet->Initialise(position + bulletLaunchPosition, bulletVelocity, 4.0f, false, true);

			timeUntilAttack = rand() % 100 / 10.0f;

		}

	}

	else
	{

	}

	position = position + velocity * frameTime;
}

IShape2D& Enemy::GetShape()
{
	return collisionShape;
}

void Enemy::ProcessCollision(GameObject& collidedWith)
{
	//Deactivate();
}

void Enemy::SetTarget(Spaceship* pTheTarget)
{
	pTarget = pTarget;
}

void Enemy::HandleMessage(Message& msg)
{
	if (msg.type == EventType::OBJECT_DESTROYED && msg.pSource == pTarget)
	{
		pTarget = nullptr;
	}

	if (msg.type == EventType::PLAYER_SPAWNED)
	{
		pTarget = msg.pSource;
	}
}
