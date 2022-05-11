#include "GameObject.h"
#include "ObjectManager.h"
#include "SoundFX.h"

ObjectManager* GameObject::pTheObjectManager = nullptr;

SoundFX* GameObject::pTheSoundFX = nullptr;

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

void GameObject::SetSoundFX(SoundFX* pSoundFX)
{
	pTheSoundFX = pSoundFX;
}

void GameObject::LoadImage(const wchar_t filename[])
{
	pic = MyDrawEngine::GetInstance()->LoadPicture(filename);
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

//true bullet type means from player
bool GameObject::getBulletType()
{
	return splittable;
}

Vector2D GameObject::getPosition()
{
	return position;
}

float GameObject::getAngle()
{
	return angle;
}

void GameObject::ProcessCollision(GameObject& collidedWith)
{
	//default collision process is to do nothing
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