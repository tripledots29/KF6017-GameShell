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
		if (pNext->IsActive())
		{
			pNext->Update(frameTime);
		}
	}
}

void ObjectManager::RenderAll()
{
	for (GameObject* pNext : pObjectList)
	{
		if (pNext->IsActive())
		{
			pNext->Render();
		}
	}
}

void ObjectManager::DeleteAllInactive()
{
	for (GameObject* pNext : pObjectList)
	{
		if (!pNext->IsActive())
		{
			delete pNext;
			pNext = nullptr;
			pObjectList.clear();
		}
	}

}

void ObjectManager::DeleteAllEnd()
{
	for (GameObject* pNext : pObjectList)
	{
		delete pNext;
	}

	pObjectList.clear();
}