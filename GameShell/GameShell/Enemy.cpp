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
	velocity.set(0.0f, 0.0f);
	LoadImage(L"boss.bmp");
}

void Enemy::Update(float frameTime)
{
	//update hitbox each frame
	collisionShape.PlaceAt(position.YValue + size, position.XValue - size, position.YValue - size, position.XValue + size); //exact square around the bullet
}

IShape2D& Enemy::GetShape()
{
	return collisionShape;
}


void Enemy::ProcessCollision(GameObject& collidedWith)
{
	Deactivate();
}
