#pragma once
#include "GameObject.h"
#include "ObjectManager.h"

class Spaceship;
class Game;

class LevelManager : public GameObject
{
protected:
	Rectangle2D collisionShape;

	int levelNumber = 0;
	int scoreTotal = 0;
	float endLevelTimer;
	bool endOfLevel;
	bool gameOver;

	int numberOfEnemies = 10;

	int playerLives = 5;
	int playerHealth;

	Spaceship* pThePlayer;
	Game* pTheGame;

public:
	LevelManager();
	~LevelManager();

	void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable) override;
	void Render() override;
	void Update(float frameTime) override;
	IShape2D& GetShape() override;
	void HandleMessage(Message& msg) override;

	void StartLevel();
	void AddScore(int score);
	void EnemyDead();
	void PlayerDead();
	void GenerateRocks(int amountOfRocks);
	void GenerateEnemies(int amountofEnemies);
};