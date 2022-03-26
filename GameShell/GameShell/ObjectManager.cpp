#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	DeleteAllEnd();
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
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
	MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);

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

void ObjectManager::CheckAllCollisions()
{

	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			if ((*it1) && (*it2) && ((*it1)->GetShape().Intersects((*it2)->GetShape())))
			{
				(*it1)->ProcessCollision(**it2);
				(*it2)->ProcessCollision(**it1);

			}
		}
	}
}