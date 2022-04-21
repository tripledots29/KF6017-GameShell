#include "LevelManager.h"

LevelManager::LevelManager() :GameObject(ObjectType::LEVELMANAGER)
{
	objectActive = false;
}

LevelManager::~LevelManager()
{

}

//bloat functions
void LevelManager::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{

}

void LevelManager::Update(float frameTime)
{

}

IShape2D& LevelManager::GetShape()
{
	return collisionShape;
}


//useful functions
void LevelManager::StartLevel()
{
	levelNumber++;
	
	if (levelNumber == 1)

		numberOfEnemies = 15;
	{
		GameObject* pTheSpaceShip = pTheObjectManager->Create(ObjectType::SPACESHIP);
		pTheSpaceShip->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);

		GenerateRocks(15);

	}
}

void LevelManager::AddScore(int score)
{
	scoreTotal = scoreTotal + score;
}

void LevelManager::EnemyDead()
{
	numberOfEnemies = numberOfEnemies - 1;
}

void LevelManager::PlayerDead()
{
	playerLives = playerLives - 1;
}

void LevelManager::GenerateRocks(int amountOfRocks)
{
	for (int i = 0; i < amountOfRocks; i++)
	{
		GameObject* pTheRock = pTheObjectManager->Create(ObjectType::ROCK);
		Vector2D pos;
		Vector2D vel;
		pos.setBearing(rand() % 628 / 100.0f, rand() % 400 + 600.0f);
		vel.set(rand() % 200 + (-100.0f), rand() % 200 + (-100.0f));
		pTheRock->Initialise(pos, vel, 64.0f, true, true);
	}
}
