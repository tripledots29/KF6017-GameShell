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

	MyDrawEngine::GetInstance()->WriteText(10, 1, L"Level:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 1, levelNumber, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 50, L"Timer Remaining:", MyDrawEngine::YELLOW);
	if (endLevelTimer > 0.0f)
	{
		MyDrawEngine::GetInstance()->WriteInt(200, 50, int(endLevelTimer), MyDrawEngine::YELLOW);
	}

	MyDrawEngine::GetInstance()->WriteText(10, 100, L"Enemies Remaining:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 100, enemiesLeft, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 150, L"Score:", MyDrawEngine::YELLOW);
	MyDrawEngine::GetInstance()->WriteInt(200, 150, scoreTotal, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteText(10, 300, L"Player Health:", MyDrawEngine::LIGHTRED);
	MyDrawEngine::GetInstance()->WriteInt(200, 300, playerHealth, MyDrawEngine::LIGHTRED);

	MyDrawEngine::GetInstance()->WriteText(10, 350, L"Lives Remaining:", MyDrawEngine::LIGHTRED);
	MyDrawEngine::GetInstance()->WriteInt(200, 350, playerLives, MyDrawEngine::LIGHTRED);


	endLevelTimer = endLevelTimer - frameTime;
	if (endLevelTimer < 0.0f && levelNumber != MAXLEVELNUMBER)
	{
		endOfLevel = true;
	}

	if (endLevelTimer < 0.0f && levelNumber == MAXLEVELNUMBER)
	{
		gameOver = true;
	}

	enemySpawnTimer = enemySpawnTimer - frameTime;
	if (enemySpawnTimer < 0.0f)
	{
		GenerateEnemies(int((rand() % 20 + 10.0f) / 10.0f));
		enemySpawnTimer = (rand() % 100 + 50) / 10.0f;
	}

	RockSpawnTimer = RockSpawnTimer - frameTime;
	if (RockSpawnTimer < 0.0f)
	{
		GenerateRocks(int((rand() % 30 + 10.0f) / 10.0f));
		RockSpawnTimer = (rand() % 50 + 50) / 10.0f;
	}

	if (gameOver == true)
	{

		pTheObjectManager->DeleteAllButLevelManager(this);

		if (pTheSoundFX)
		{
			pTheSoundFX->StopPlayingAlertSound();
			pTheSoundFX->StopPlayingEngineSound();
		}

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 250, L"GAME OVER", MyDrawEngine::RED);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 500, L"Final Score:", MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->WriteInt(halfWidth + 150, 500, scoreTotal, MyDrawEngine::RED);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 700, L"Press G to Quit", MyDrawEngine::WHITE);


		if (pInputs->KeyPressed(DIK_G))
		{
			if (pTheSoundFX)
			{
				pTheSoundFX->PlaySelect();
			}

			Game::instance.EndGame();
		}
	}

	else if (endOfLevel == true)
	{
		pTheObjectManager->DeleteAllButLevelManager(this);

		if (pTheSoundFX)
		{
			pTheSoundFX->StopPlayingAlertSound();
			pTheSoundFX->StopPlayingEngineSound();
		}

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 250, L"LEVEL ", MyDrawEngine::YELLOW);
		MyDrawEngine::GetInstance()->WriteInt(halfWidth + 100, 250, levelNumber, MyDrawEngine::YELLOW);
		MyDrawEngine::GetInstance()->WriteText(halfWidth + 150, 250, L" COMPLETE", MyDrawEngine::YELLOW);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 500, L"Score So Far:", MyDrawEngine::YELLOW);
		MyDrawEngine::GetInstance()->WriteInt(halfWidth + 150, 500, scoreTotal, MyDrawEngine::YELLOW);

		MyDrawEngine::GetInstance()->WriteText(halfWidth, 700, L"Press G to Continue", MyDrawEngine::WHITE);

		if (pInputs->KeyPressed(DIK_G))
		{
			if (pTheSoundFX)
			{
				pTheSoundFX->PlaySelect();
			}

			endOfLevel = false;

			StartLevel();
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

	enemiesSpawned = 0;
	levelNumber++;

	if (levelNumber == 1)
	
	{
		endLevelTimer = 50.0f;
		enemySpawnTimer = 5.0f;
		RockSpawnTimer = 2.0f;

		maxNumEnemies = 5;
		enemiesLeft = maxNumEnemies;

		maxNumRocks = 10;

		GeneratePlayer();

	}

	if (levelNumber == 2)
	{
		endLevelTimer = 100.0f;
		enemySpawnTimer = 5.0f;
		RockSpawnTimer = 2.0f;

		maxNumEnemies = 10;
		enemiesLeft = maxNumEnemies;

		maxNumRocks = 20;

		GeneratePlayer();

	}

	if (levelNumber == 3)
	{
		endLevelTimer = 150.0f;
		enemySpawnTimer = 5.0f;
		RockSpawnTimer = 2.0f;

		maxNumEnemies = 20;
		enemiesLeft = maxNumEnemies;

		maxNumRocks = 30;

		GeneratePlayer();

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
		}
	}

	if (msg.type == EventType::PLAYER_SPAWNED && msg.pSource == pThePlayer)
	{
		playerHealth = msg.otherData;
	}

	if (msg.type == EventType::ENEMY_DESTROYED)
	{
		EnemyDead();
		AddScore(5);
	}

	if (msg.type == EventType::ROCK_EXPLODE)
	{
		AddScore(int(msg.otherData / 32));
	}

}

void LevelManager::AddScore(int score)
{
	scoreTotal = scoreTotal + score;
}

void LevelManager::EnemyDead()
{
	enemiesLeft = enemiesLeft - 1;
}

void LevelManager::PlayerDead()
{
	playerLives = playerLives - 1;
}

void LevelManager::GenerateRocks(int amountOfRocks)
{
	for (int i = 0; i < amountOfRocks; i++)
	{
		if (rocksSpawned < maxNumRocks)
		{
			GameObject* pTheRock = pTheObjectManager->Create(ObjectType::ROCK);
			Vector2D pos;
			Vector2D vel;
			pos.XValue = pThePlayer->getPosition().XValue + 2500.0f;
			pos.YValue = pThePlayer->getPosition().YValue + (rand() % 1000 - 500.0f);
			vel.set(rand() % 400 - 250.0f, rand() % 400 - 250.0f);
			pTheRock->Initialise(pos, vel, 64.0f, true, true);
			rocksSpawned++;
		}
	}
}

void LevelManager::GenerateEnemies(int amountOfEnemies)
{
	for (int i = 0; i < amountOfEnemies; i++)
	{
		if (enemiesSpawned < maxNumEnemies)
		{
			GameObject* pTheEnemy = pTheObjectManager->Create(ObjectType::ENEMY);
			Vector2D pos;
			Vector2D vel;
			pos.XValue = pThePlayer->getPosition().XValue + 3000.0f;
			pos.YValue = pThePlayer->getPosition().YValue + (rand() % 1000 - 500.0f);
			vel.set(rand() % 400 + (-100.0f), rand() % 400 + (-100.0f));
			pTheEnemy->Initialise(pos, vel, 64.0f, false, true);
			(dynamic_cast <Enemy*> (pTheEnemy))->SetTarget(pThePlayer);
			enemiesSpawned++;
		}
	}

}

void LevelManager::GeneratePlayer()
{
	pThePlayer = dynamic_cast <Spaceship*> (pTheObjectManager->Create(ObjectType::SPACESHIP));
	if (pThePlayer)
	{
		pThePlayer->Initialise(Vector2D(20.0f, 20.0f), Vector2D(20.0f, 20.0f), 32.0f, false, true);
	}
}

