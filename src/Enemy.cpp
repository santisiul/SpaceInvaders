#include "Enemy.h"

string Enemy::mesh = "Cube.mesh";
string Enemy::material = "red";

Enemy::Enemy(): GameObject(mesh, material){ 
	dir=1; 
	setCollider(0.8);
	setTag("enemy");
	speed = 8;
}
Enemy::Enemy(Ogre::SceneNode* parent): GameObject(mesh, material, parent){ 
	dir=1; 
	setCollider(0.8);
	setTag("enemy");
	speed = 8;
} 
void Enemy::deactivate(){
	GameObject::deactivate();
	getNode()->setPosition(Ogre::Vector3(-30,0,80));
}

void Enemy::update(Ogre::Real deltaT){
	Ogre::Vector3 pos = getNode()->getPosition();

	if (pos.x < -40)	dir = 1;
	if (pos.x > 40) 	dir = -1;
	getNode()->translate(dir * deltaT * speed, 0, 0);
}

void Enemy::onCollision(GameObject* collision){
	/*if(getTag() != collision->getShooter()->getTag()){
		deactivate();
		
	}*/	
}

bool Enemy::shoot(Ogre::Vector3 player){
	Ogre::Vector3 pos = getNode()->getPosition();
	int rango = 10;
	if(pos.x > (player.x-rango) && pos.x < (player.x+rango)){
		return true;
	}
	return false;
}