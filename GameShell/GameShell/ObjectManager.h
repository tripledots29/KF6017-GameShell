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

class GameObject;

class ObjectManager
{
protected:
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
	void CheckAllCollisions();

};
