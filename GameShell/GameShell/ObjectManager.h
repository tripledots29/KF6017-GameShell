#pragma once
#include <list>
#include "Bullet.h"
#include "Explosion.h"
#include "Rock.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "LevelManager.h"
#include "ObjectType.h"
#include "Message.h"
#include "Puff.h"

class GameObject;

class ObjectManager
{
private:
	 std::list<GameObject*> pObjectList;

public:
	ObjectManager();
	~ObjectManager();

	void AddObject(GameObject* pNewObject);
	GameObject* Create(ObjectType type);
	void SendMessage(Message msg);
	void UpdateAll(float frameTime);
	void RenderAll();
	void DeleteAllInactive();
	void DeleteAllEnd();
	void DeleteAllButLevelManager(GameObject* pLevelManager);
	void CheckAllCollisions();

};
