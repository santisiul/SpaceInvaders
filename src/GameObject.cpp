#include "GameObject.h"

GameObject::GameObject(string mesh, string material){
	Ogre::SceneManager* _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
	createNode(mesh, material, _sceneMgr->getRootSceneNode());
	activate();
	radiusCollider = 1;
	tag = "untagged";
}

GameObject::GameObject(string mesh, string material, Ogre::SceneNode* parent){
	createNode(mesh, material, parent);
	activate();
	radiusCollider = 1;
	tag = "untagged";
}

GameObject::~GameObject(){}

void GameObject::activate(){ enable = true; }
void GameObject::deactivate(){ enable = false; }
bool GameObject::isActive(){ return enable; }

string GameObject::getTag() const{ return tag; }

void GameObject::setTag(string tag){ this->tag = tag; }

Ogre::SceneNode* GameObject::getNode() const{ return node; }

void GameObject::setCollider(int radius){ radiusCollider = radius; }
int GameObject::getCollider() const{ return radiusCollider; }

void GameObject::createNode(string mesh, string material, Ogre::SceneNode* parent){

	Ogre::SceneManager* _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
	Ogre::Entity* entTmp = _sceneMgr->createEntity(mesh);
	Ogre::SceneNode* nodeTmp = _sceneMgr->createSceneNode();
	entTmp->setMaterialName(material);
	nodeTmp->attachObject(entTmp);
	nodeTmp->setPosition(Ogre::Vector3(0,0,0));

	parent->addChild(nodeTmp);
	node = nodeTmp;
}

void GameObject::update(){}
void GameObject::onCollision(GameObject* gO){}