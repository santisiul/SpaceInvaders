#include "Enemy.h"

string Enemy::mesh = "Cube.mesh";
string Enemy::material = "red";

Enemy::Enemy(): GameObject(mesh, material){ dir=1; }
Enemy::Enemy(Ogre::SceneNode* parent): GameObject(mesh, material, parent){ dir=1; } 

void Enemy::update(){
	Ogre::Vector3 pos = getNode()->getPosition();

	if (pos.x < -30)	dir = 1;
	if (pos.x > 30) 	dir = -1;

	pos+=Ogre::Vector3(0.1 * dir,0,0);
	getNode()->setPosition(pos);
}