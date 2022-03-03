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
	~GameObject();
	void LoadImage(const wchar_t filename[]);
	void Render();
	virtual void Update(float frameTime) = 0;
};
