#pragma once
#include "Vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include "gametimer.h"
#include "Shapes.h"
#include <typeinfo>
#include "ObjectType.h"
#include "Message.h"

class ObjectManager;

class SoundFX;

class GameObject
{
protected:
	Vector2D position = Vector2D(0, 0); //default is 0,0 for ease
	float angle = 0; //angle default is 0 for ease
	float imageScale = 1; //scale the object is on (originally 1)
	float bmpRadius; //original radius object has from the bmp file
	float size;  //actual size of the object (half width)
	PictureIndex pic = 0; //default is 0 for reduced memory
	bool objectActive = false; //default is false till activated
	bool canCollide = true;  //default is can collide
	bool splittable = false; //default is can't split
	static ObjectManager* pTheObjectManager;
	static SoundFX* pTheSoundFX;
	const ObjectType TYPE;


public:
	GameObject(ObjectType type);
	virtual ~GameObject(); //using a virtual destructor means the compiler decides what to delete at run-time rather than compile-time.
						   //means that deleting a GameObject is not just deleting the extra stuff (e.g. the add-on a rock has) but everything.
	static void SetObjectManager(ObjectManager* pObjectManager);
	static void SetSoundFX(SoundFX* pSoundFX);
	void LoadImage(const wchar_t filename[]);
	bool IsActive() const;
	void Deactivate();
	virtual void HandleMessage(Message& msg);
	virtual void Initialise(Vector2D initialPosition, Vector2D initialVelocity, float initialSize, bool isSplittable, bool isCollidable)  = 0;
	virtual void Render();
	float GetSize();
	ObjectType getType() const;
	bool getCollide();
	bool getBulletType();
	Vector2D getPosition();	
	float getAngle();
	virtual void Update(float frameTime) = 0;
	virtual IShape2D& GetShape() = 0;
	virtual void ProcessCollision(GameObject& collidedWith);

};
