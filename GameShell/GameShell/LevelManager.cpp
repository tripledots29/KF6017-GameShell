#include "LevelManager.h"
#include "gamecode.h"

LevelManager::LevelManager() :GameObject(ObjectType::LEVELMANAGER)
{
	objectActive = false;
	canCollide = false;
	pThePlayer = nullptr;
	
}

LevelManager::~LevelManager()
{

}

int halfWidth = 800;

//bloat functions
void LevelManager::Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)
{

}

void LevelManager::Render()
{

}

void LevelManager::Update(float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	endLevelTimer = endLevelTimer - frameTime;

	MyDrawEngine::GetInstance()->WriteText(10, 1, L"Level:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 1, levelNumber, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 50, L"Timer Remaining:", MyDrawEngine::YELLOW);
	if (endLevelTimer > 0.0f)
	{
		MyDrawEngine::GetInstance()->WriteInt(200, 50, int(endLevelTimer), MyDrawEngine::YELLOW);
	}

	if (endLevelTimer < 0.0f)
	{
		endOfLevel = true;
	}

	MyDrawEngine::GetInstance()->WriteText(10, 100, L"Enemies Remaining:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 100, numberOfEnemies, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 150, L"Player Health:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 150, playerHealth, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 200, L"Score:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 200, scoreTotal, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 250, L"Lives Remaining:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 250, playerLives, MyDrawEngine::YELLOW);




	if (endOfLevel == true)
	{
		pTheObjectManager->DeleteAllButLevelManager(this);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 250, L"LEVEL OVER", MyDrawEngine::YELLOW);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 500, L"Score So Far:", MyDrawEngine::YELLOW);
		MyDrawEngine::GetInstance()->WriteInt(halfWidth + 150, 500, scoreTotal, MyDrawEngine::YELLOW);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 700, L"Press G to Continue", MyDrawEngine::WHITE);

		if (pInputs->KeyPressed(DIK_G))
		{
			endOfLevel = false;

			StartLevel();
		}

	}

	if (gameOver == true)
	{
		
		MyDrawEngine::GetInstance()->WriteText(halfWidth, 250, L"GAME OVER", MyDrawEngine::RED);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 500, L"Final Score:", MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->WriteInt(halfWidth + 150, 500, scoreTotal, MyDrawEngine::RED);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 700, L"Press G to Quit", MyDrawEngine::WHITE);


		if (pInputs->KeyPressed(DIK_G))
		{
			Game::instance.EndGame();
		}
	}
	
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
	
	{
		endLevelTimer = 1000.0f;
		numberOfEnemies = 5;
		numberOfRocks = 0;

		GenerateRocks(numberOfRocks);

		GenerateEnemies(numberOfEnemies);

		pThePlayer = dynamic_cast <Spaceship*> (pTheObjectManager->Create(ObjectType::SPACESHIP));
		if (pThePlayer)
		{
			pThePlayer->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);
		}

	}

	if (levelNumber == 2)
	{
		endLevelTimer = 10.0f;
		numberOfEnemies = 10;
		numberOfRocks = 15;

		GenerateRocks(numberOfRocks);

		GenerateEnemies(numberOfEnemies);

		pThePlayer = dynamic_cast <Spaceship*> (pTheObjectManager->Create(ObjectType::SPACESHIP));
		if (pThePlayer)
		{
			pThePlayer->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);
		}

	}

	if (levelNumber == 3)
	{
		endLevelTimer = 250.0f;
		numberOfEnemies = 15;
		numberOfRocks = 25;

		GenerateRocks(numberOfRocks);

		GenerateEnemies(numberOfEnemies);

		pThePlayer = dynamic_cast <Spaceship*> (pTheObjectManager->Create(ObjectType::SPACESHIP));
		if (pThePlayer)
		{
			pThePlayer->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);
		}
	}


}

void LevelManager::HandleMessage(Message& msg)
{
	if (msg.type == EventType::PLAYER_HIT)
	{
		playerHealth = msg.otherData;
	}

	if (msg.type == EventType::PLAYER_DESTROYED && msg.pSource == pThePlayer)
	{
		PlayerDead();

		if (playerLives <= 0)
		{
			gameOver = true;
		}

		else
		{
			pThePlayer = nullptr;
			pThePlayer = dynamic_cast <Spaceship*> (pTheObjectManager->Create(ObjectType::SPACESHIP));
			pThePlayer->Initialise(Vector2D(msg.location.XValue + 200.0f, msg.location.YValue), Vector2D(550.0f, 50.0f), 32.0f, false, true);
			//playerHealth = msg.otherData;
		}
	}

	if (msg.type == EventType::PLAYER_SPAWNED && msg.pSource == pThePlayer)
	{
		playerHealth = msg.otherData;
	}

	if (msg.type == EventType::ENEMY_DESTROYED)
	{
		EnemyDead();
	}

	if (msg.type == EventType::ROCK_EXPLODE)
	{
		scoreTotal++;
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
	for (int i = 0; i < amountofEnemies; i++)
	{
		GameObject* pTheEnemy = pTheObjectManager->Create(ObjectType::ENEMY);
		Vector2D pos;
		Vector2D vel;
		pos.setBearing(rand() % 314 / 100.0f, rand() % 1500 + 600.0f);
		vel.set(rand() % 400 + (-100.0f), rand() % 400 + (-100.0f));
		pTheEnemy->Initialise(pos, vel, 32.0f, false, true);
		(dynamic_cast <Enemy*> (pTheEnemy))->SetTarget(pThePlayer);
	}
}