#pragma once
#include "Vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include "gametimer.h"
#include "Shapes.h"
#include <typeinfo>

//enum class ObjectType{UNKNOWN, SPACESHIP, ROCK, BULLET};

class GameObject
{
protected:
	Vector2D position;
	float angle;
	float imageScale = 1; //scale the object is on (originally 1)
	float bmpRadius; //original radius object has from the bmp file
	float size;  //actual size of the object (half width)
	PictureIndex pic;
	SoundIndex sound;
	bool objectActive;
	bool canCollide; 
	//ObjectType type;


public:
	GameObject();
	virtual ~GameObject(); //using a virtual destructor means the compiler decides what to delete at run-time rather than compile-time.
						   //means that deleting a GameObject is not just deleting the extra stuff (e.g. the add-on a rock has) but everything.
	
	void LoadImage(const wchar_t filename[]);
	void PlaySound(const wchar_t filename[]);
	bool IsActive() const;
	void Deactivate();
	virtual void Render();
	//void SetScale(float scale);
	bool getCollide();
	Vector2D getPosition();
	virtual void Update(float frameTime) = 0;
	virtual IShape2D& GetShape() = 0;
	virtual void ProcessCollision(GameObject& collidedWith);
	//const type_info& GetType(); //try this next workshop
	//ObjectType GetType() const;
};
