#include "Fisics.h"

Fisics::Fisics(){}

void Fisics::subscribe(GameObject* gameObject){
	gameObjects.push_back(gameObject);
}

void Fisics::calculateCollisions(){
	//std::vector<GameObject*>::iterator it;
	float squaredDistance = 500;
	for (std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i)
	{
		//se comprueba si esta activo el objeto
		if((*i)->isActive()){
			//it = i;
			//Ogre::Vector3 pos = (*i)->getNode()->getPosition();
			for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
			{
				//Se comprueba que sean diferente tipos de objetos y que segundo objeto este activo
				if((*it)->getTag() != (*i)->getTag() && (*it)->isActive()){

					squaredDistance = (*i)->getCollider() + (*it)->getCollider();
					squaredDistance *= squaredDistance;

					if((*i)->getNode()->getPosition().squaredDistance((*it)->getNode()->getPosition()) < squaredDistance){
						(*it)->onCollision(*i);
						(*i)->onCollision(*it);
					}
				}
				
			}
		}
		
	}
}