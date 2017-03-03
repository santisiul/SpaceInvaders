#ifndef Enemy_H
#define Enemy_H

#include "GameObject.h"

class Enemy: public GameObject
{
public:
	Enemy();
	Enemy(Ogre::SceneNode* parent);
	~Enemy();

	void update();
	void onCollision(GameObject* gameObject);

private:
	int dir;
	static string mesh;
	static string material;
	
};

#endif