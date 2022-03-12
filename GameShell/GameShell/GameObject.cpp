#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::LoadImage(const wchar_t filename[])
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	pic = pDE->LoadPicture(filename);
}

bool GameObject::IsActive() const
{
	return objectActive;
}

void GameObject::Deactivate() 
{
	objectActive = false;
}

void GameObject::Render()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	pDE->DrawAt(position, pic, 2, angle); //2.0f, 0.5f, 0.8f
}