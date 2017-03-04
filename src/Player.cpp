#include "Player.h"

Player::Player(string mesh, string material): GameObject(mesh, material){ 
	setTag("player");
	setCollider(1);
	speed = 15;
}
//Player::Player(string mesh, string nameNode, string material, Ogre::SceneNode* parent): GameObject(mesh, nameNode, material, parent){}

void Player::update(Ogre::Real axisX, Ogre::Real deltaT){
	
	//Ogre::Vector3 pos = getNode()->getPosition();
	int x;
	if (axisX > 0)	x = 1;
	else if(axisX < 0) x = -1;

	getNode()->translate(x * deltaT * speed, 0, 0);
	//pos += Ogre::Vector3(x,0,0);
	//getNode()->setPosition(pos);

}

void Player::onCollision(GameObject* gameObject){
	
}