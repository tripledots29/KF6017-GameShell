#pragma once
#include "Vector2D.h"
#include "mydrawengine.h"
#include "myinputs.h"
#include "gametimer.h"

class GameObject
{
protected:
	Vector2D position;
	float angle;
	PictureIndex pic;
	bool objectActive;

public:
	GameObject();
	virtual ~GameObject(); //using a virtual destructor means the compiler decides what to delete at run-time rather than compile-time.
						   //means that deleting a GameObject is not just deleting the extra stuff (e.g. the add-on a rock has) but everything.
	void LoadImage(const wchar_t filename[]);
	bool IsActive() const;
	void Deactivate();
	void Render();
	virtual void Update(float frameTime) = 0;
};
