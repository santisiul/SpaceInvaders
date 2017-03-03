#include "Projectile.h"

string Projectile::mesh = "bullet.mesh";
string Projectile::material = "green";

Projectile::Projectile(): GameObject(mesh, material){/*activate();*/ }
Projectile::Projectile(Ogre::SceneNode* parent): GameObject(mesh, material, parent){ /*activate();*/ }

void Projectile::update(){
	Ogre::Vector3 pos = getNode()->getPosition();

	if(pos.z < -100){
		deactivate();
		getNode()->setPosition(Ogre::Vector3(0,0,80));
	} 
	else{
		pos += Ogre::Vector3(0,0,-0.1);
		getNode()->setPosition(pos);
	}
	
}