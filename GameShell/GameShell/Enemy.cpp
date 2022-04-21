#include "Enemy.h"

Enemy::Enemy() :GameObject(ObjectType::ENEMY)
{
	objectActive = false;
	bmpRadius = 4.0f;
}

Enemy::~Enemy()
{

}


void Enemy::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{

}

void Enemy::Update(float frameTime)
{
	//update hitbox each frame
	//collisionShape.PlaceAt(position.YValue + size, position.XValue - size, position.YValue - size, position.XValue + size); //exact square around the bullet
}

IShape2D& Enemy::GetShape()
{
	return collisionShape;
}


void Enemy::ProcessCollision(GameObject& collidedWith)
{
	Deactivate();
}
