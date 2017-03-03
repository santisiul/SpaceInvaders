
#ifndef GameObject_H
#define GameObject_H 

#include <Ogre.h>
//#include <string.h>

using namespace std;

class GameObject
{
  public:
	GameObject(string mesh, string material);
	GameObject(string mesh, string material, Ogre::SceneNode* parent);

	~GameObject();

	void activate();
	void deactivate(); 
	bool isActive();
	string getTag() const;
	void setTag(string tag);

	Ogre::SceneNode* getNode() const;
	void setCollider(int radius);
	int getCollider () const;

	virtual void update();
	virtual void onCollision(GameObject* gO);

  private:
	Ogre::SceneNode* node;
	bool enable;
	string tag;
	int radiusCollider;

	void createNode(string mesh, string material, Ogre::SceneNode* parent);

	
};

#endif