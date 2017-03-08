#include "Projectile.h"
#include "PlayState.h"

string Projectile::mesh = "bullet.mesh";
string Projectile::material = "green";

Projectile::Projectile(): GameObject(mesh, material){ 
	deactivate(); 
	setCollider(1);
	setTag("projectile");
	speed = 50;
	dir = 1;
}
Projectile::Projectile(Ogre::SceneNode* parent): GameObject(mesh, material, parent){
	deactivate(); 
	setCollider(1);
	setTag("projectile");
	speed = 50;
	dir = 1;
}
Projectile::~Projectile(){}

GameObject* Projectile::getShooter() const{ return shooter; }

void Projectile::start(GameObject* shooter){ 
	Ogre::Vector3 pos = shooter->getNode()->getPosition();
	activate();
	this->shooter = shooter;
	
	if(shooter->getTag() == "player"){ 
		dir = -1; 
		getNode()->setPosition(pos += Ogre::Vector3(0,0,-2));
	}
	else{ 
		dir = 1; 
		getNode()->setPosition(pos += Ogre::Vector3(0,0,2));
	}
}

void Projectile::update(Ogre::Real deltaT){
	Ogre::Vector3 pos = getNode()->getPosition();	
	
	if(pos.z < -100 || pos.z > 50){
		deactivate();
		getNode()->setPosition(Ogre::Vector3(0,0,80));
	} 
	else{
		getNode()->translate(0, 0, dir * deltaT * speed);
	}
}

void Projectile::onCollision(GameObject* collision){
	if(shooter->getTag() != collision->getTag()){
		PlayState::getSingletonPtr()->soundExplode();
		
		deactivate();
		getNode()->setPosition(Ogre::Vector3(0,0,80));
		if(collision->getTag() != "player")
			collision->deactivate();

		if(collision->getTag() == "enemy")
			PlayState::getSingletonPtr()->destroyEnemy();
	}	
}