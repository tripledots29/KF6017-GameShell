#include "GameObject.h"
#include "ObjectManager.h"

ObjectManager* GameObject::pTheObjectManager = nullptr;

GameObject::GameObject(ObjectType type):TYPE(type)
{

}

GameObject::~GameObject()
{

}

void GameObject::SetObjectManager(ObjectManager* pObjectManager)
{
	pTheObjectManager = pObjectManager;
}

void GameObject::LoadImage(const wchar_t filename[])
{
	pic = MyDrawEngine::GetInstance()->LoadPicture(filename);
}


void GameObject::PlaySound(const wchar_t filename[])
{
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	sound = pSE->LoadWav(filename);
	pSE->Play(sound); 

}

bool GameObject::IsActive() const
{
	return objectActive;
}

void GameObject::Deactivate() 
{
	objectActive = false;
}

void GameObject::HandleMessage(Message& msg)
{
	//Default handling of a message is to do nothing
}

void GameObject::Render()
{
	if (objectActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, pic, imageScale, angle, 0); //position, picture, scale, angle, transparancy (0 = opaque)
	}
}

float GameObject::GetSize()
{
	return size;
}

/*
void GameObject::SetScale(float scale)
{
	imageScale = scale;
}
*/

ObjectType GameObject::getType() const
{
	return TYPE;
}

bool GameObject::getCollide()
{
	return canCollide;
}

Vector2D GameObject::getPosition()
{
	return position;
}

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