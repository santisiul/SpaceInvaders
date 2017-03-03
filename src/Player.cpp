#include "Player.h"

Player::Player(string mesh, string material): GameObject(mesh, material){}
//Player::Player(string mesh, string nameNode, string material, Ogre::SceneNode* parent): GameObject(mesh, nameNode, material, parent){}

void Player::update(float axisX){
	
	Ogre::Vector3 pos = getNode()->getPosition();
	float x;
	if (axisX >0)	x = 0.1;
	else if(axisX < 0) x = -0.1;

	pos += Ogre::Vector3(x,0,0);
	getNode()->setPosition(pos);

}