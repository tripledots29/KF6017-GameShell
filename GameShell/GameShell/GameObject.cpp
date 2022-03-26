#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::LoadImage(const wchar_t filename[])
{
	pic = MyDrawEngine::GetInstance()->LoadPicture(filename);
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
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, pic, imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

/*
void GameObject::SetScale(float scale)
{
	imageScale = scale;
}
*/

void GameObject::ProcessCollision(GameObject& collidedWith)
{
	Deactivate();
	//default collision process is to deactivate
}

/*
//try this in next workshop
const type_info& GameObject::GetType()
{
	return typeid(*this);
}
*/

/*
ObjectType GameObject::GetType() const
{
	return type;
}
*/