#include "GameObject.h"

class Spaceship : public GameObject
{
private:
	Vector2D velocity;

public:
	Spaceship();
	~Spaceship();
	void Intialise(Vector2D initialPosition);
	void Update(float frameTime) override;
};
