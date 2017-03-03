#ifndef FISICS_H
#define FISICS_H 

#include "GameObject.h"

class Fisics
{
public:
	Fisics();
	~Fisics();

	void subscribe(GameObject* gameObject);
	void calculateCollisions();

private:
	std::vector<GameObject*> gameObjects;
	
};
#endif