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


void GameObject::PlaySound(const wchar_t filename[])
{
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	sound = pSE->LoadWav(filename);
	pSE->Play(sound); //ASK CHRIS WHY THIS IS UNDERLINED

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
	pDE->DrawAt(position, pic, 1.5, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
}