#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager::ObjectManager()
{
	GameObject::SetObjectManager(this);
}

ObjectManager::~ObjectManager()
{
	DeleteAllEnd();
	GameObject::SetObjectManager(nullptr);
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

GameObject* ObjectManager::Create(ObjectType type)
{
	GameObject* pNewObject = nullptr;

	if (type == ObjectType::BULLET)
	{
		pNewObject = new Bullet();
	}

	else if (type == ObjectType::EXPLOSION)
	{
		pNewObject = new Explosion();
	}

	else if (type == ObjectType::ROCK)
	{
		pNewObject = new Rock();
	}

	else if (type == ObjectType::SPACESHIP)
	{
		pNewObject = new Spaceship();
	}

	else if (type == ObjectType::LEVELMANAGER)
	{
		pNewObject = new LevelManager();
	}

	else if (type == ObjectType::ENEMY)
	{
		pNewObject = new Enemy();
	}

	else
	{
		ErrorLogger::Write(L"Could not create item: ");
	}

	if (pNewObject)
	{
		AddObject(pNewObject);
	}

	return pNewObject;

}

void ObjectManager::SendMessage(Message msg)
{
	for (GameObject* pNext : pObjectList)
	{
		if (pNext)
		{
			pNext->HandleMessage(msg);
		}
	}
}


void ObjectManager::UpdateAll(float frameTime)
{
	for (GameObject* pNext : pObjectList)
	{
		if ((pNext) && (pNext->IsActive()))
		{
			pNext->Update(frameTime);
		}
	}
}

void ObjectManager::RenderAll()
{
	//MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);


	for (GameObject* pNext : pObjectList)
	{
		if ((pNext) && (pNext->IsActive()))
		{
			pNext->Render();
		}
	}
}

void ObjectManager::DeleteAllInactive()
{
	for (GameObject*& pNext : pObjectList)
	{
		if ((!pNext) || (!pNext->IsActive()))
		{
			delete pNext;
			pNext = nullptr;
		}
	}
	pObjectList.remove(nullptr);
}

void ObjectManager::DeleteAllEnd()
{
	for (GameObject* pNext : pObjectList)
	{
		delete pNext;
	}

	pObjectList.clear();
}

void ObjectManager::DeleteAllButLevelManager(GameObject* pLevelManager)
{
	for (GameObject* &pNext : pObjectList)
	{
		if (pNext != pLevelManager)
		{
			delete pNext;
			pNext = nullptr;

		}
	}
	pObjectList.remove(nullptr);
}

void ObjectManager::CheckAllCollisions()
{

	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		if ((*it1)->getCollide() == true)
		{
			for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
			{
				if (((*it2)->getCollide() == true) && (*it1) && (*it2) && ((*it1)->GetShape().Intersects((*it2)->GetShape())))
				{
					(*it1)->ProcessCollision(**it2);
					(*it2)->ProcessCollision(**it1);

				}
			}
		}
	}
}