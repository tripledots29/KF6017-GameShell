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

void GameObject::Render()
{

	if (objectActive == true)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, pic); //2.0f, 0.5f, 0.8f
	}

}