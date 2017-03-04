#ifndef Enemy_H
#define Enemy_H

#include "GameObject.h"

class Enemy: public GameObject
{
public:
	Enemy();
	Enemy(Ogre::SceneNode* parent);
	~Enemy();

	bool shoot(Ogre::Vector3 posPlayer);
	void update(Ogre::Real deltaT);
	void onCollision(GameObject* collision);
	void deactivate();

private:
	int dir;
	static string mesh;
	static string material;
	
};

#endif