#ifndef WAL_H
#define WAL_H

#include "GameObject.h"

class Wall: public GameObject
{
public:
	Wall(string mesh = "Cube.mesh", string material = "wall");
	~Wall();

	void deactivate();
	void onCollision(GameObject* gameObject);
	
};
#endif