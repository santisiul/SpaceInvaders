#include "Wall.h"

Wall::Wall(string mesh, string material):GameObject(mesh, material){
	setTag("wall");
}

Wall::~Wall(){}

void Wall::deactivate(){
	GameObject::deactivate();
	getNode()->setPosition(Ogre::Vector3(0,0,150));
}

void Wall::onCollision(GameObject* gameObject){

}