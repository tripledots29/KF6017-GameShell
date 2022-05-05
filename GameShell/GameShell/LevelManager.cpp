#include "LevelManager.h"

LevelManager::LevelManager() :GameObject(ObjectType::LEVELMANAGER)
{
	objectActive = false;
	canCollide = false;
}

LevelManager::~LevelManager()
{

}

//bloat functions
void LevelManager::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{
	

}

void LevelManager::Render()
{

}

void LevelManager::Update(float frameTime)
{

	MyDrawEngine::GetInstance()->WriteText(100, 50, L"Timer Remaining:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteDouble(300, 50, double(endLevelTimer), MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(400, 50, L"Enemies Remaining:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(600, 50, numberOfEnemies, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(700, 50, L"Player Health:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(900, 50, playerHealth, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(1100, 50, L"Score:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(1300, 50, scoreTotal, MyDrawEngine::YELLOW);

}

IShape2D& LevelManager::GetShape()
{
	return collisionShape;
}


//useful functions
void LevelManager::StartLevel()
{
	objectActive = true;

	levelNumber++;
	
	if (levelNumber == 1)

		numberOfEnemies = 15;
	{
		GameObject* pTheSpaceShip = pTheObjectManager->Create(ObjectType::SPACESHIP);
		pTheSpaceShip->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);

		GenerateRocks(5);

		GenerateEnemies(1);
	}
}

void LevelManager::HandleMessage(Message& msg)
{
	if (msg.type == EventType::SPACESHIP_HIT)
	{
		playerHealth = msg.otherData;
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

void LevelManager::GenerateEnemies(int amountofEnemies)
{
	GameObject* pTheEnemy = pTheObjectManager->Create(ObjectType::ENEMY);
	Vector2D pos;
	Vector2D vel;
	pos.setBearing(rand() % 628 / 100.0f, rand() % 400 + 600.0f);
	vel.set(rand() % 400 + (-100.0f), rand() % 400 + (-100.0f));
	pTheEnemy->Initialise(pos, vel, 32.0f, false, true);
}