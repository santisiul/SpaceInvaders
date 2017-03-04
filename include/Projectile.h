#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class Projectile: public GameObject
{
public:
	Projectile();
	Projectile(Ogre::SceneNode* parent);
	~Projectile();

	void update(Ogre::Real deltaT);
	void onCollision(GameObject* gameObject);
	void start(GameObject* shooter);
	GameObject* getShooter() const;
	//void GameObject::deactivate();

private:
	static string mesh;
	static string material;

	GameObject* shooter;
	int dir;
};
#endif