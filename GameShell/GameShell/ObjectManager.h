#pragma once
#include <list>
#include "GameObject.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Rock.h"
#include "Spaceship.h"
class ObjectManager
{
protected:
	 std::list<GameObject*> pObjectList;

public:
	ObjectManager();
	~ObjectManager();

	void AddObject(GameObject* pNewObject);
	GameObject* Create(std::wstring name);
	void UpdateAll(float frameTime);
	void RenderAll();
	void DeleteAllInactive();
	void DeleteAllEnd();
	void CheckAllCollisions();

};
