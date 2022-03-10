#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	DeleteAll();
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

void ObjectManager::UpdateAll(float frameTime)
{
	for (GameObject* pNext : pObjectList)
	{
		pNext->Update(frameTime);
	}
}

void ObjectManager::RenderAll()
{
	for (GameObject* pNext : pObjectList)
	{
		pNext->Render();
	}
}

void ObjectManager::DeleteAll()
{
	for (GameObject* pNext : pObjectList)
	{
		delete pNext;
	}

	pObjectList.clear();
}