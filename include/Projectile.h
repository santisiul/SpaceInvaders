#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class Projectile: public GameObject
{
public:
	Projectile();
	Projectile(Ogre::SceneNode* parent);
	~Projectile();

	void update();

private:
	static string mesh;
	static string material;
};
#endif