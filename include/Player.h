#ifndef PLAYER_H
#define PLAYER_H 

#include "GameObject.h"

class Player: public GameObject
{
public:
	Player(string mesh = "Sphere.mesh", string material = "red");
	//Player(string mesh, string nameNode, string material, Ogre::SceneNode* parent);
	~Player();

	void update(float axisX);
	void onCollision(GameObject* gameObject);
	
};
#endif