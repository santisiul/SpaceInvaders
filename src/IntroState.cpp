#include "IntroState.h"
#include "PlayState.h"


template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  if(_root->hasSceneManager("SceneManager")){
    _sceneMgr = _root->getSceneManager("SceneManager");
    _camera = _sceneMgr->getCamera("IntroCamera");
  }
  else{
    _sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    _camera = _sceneMgr->createCamera("IntroCamera");
  }

  
  _camera->setPosition(Ogre::Vector3(0,40,70));
  _camera->lookAt(Ogre::Vector3(0,0,0));
  _camera->setNearClipDistance(5);
  _camera->setFarClipDistance(10000);

  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  _viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));


  _sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

  Ogre::SceneNode* node2 = _sceneMgr->createSceneNode("light");
  _sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE); 
  Ogre::Light* light = _sceneMgr->createLight("Light1");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(1,-1,-1));
  node2->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(node2);

  _sceneMgr->setSkyBox(true, "skybox");
  
  player = new Player();
  player->getNode()->setPosition(Ogre::Vector3(-4,30,55));
  player->getNode()->yaw(Ogre::Degree(210));

  //player = new Player("Sphere.mesh", "player", "red.material");
  //player->getNode()->setPosition(Ogre::Vector3(0,0,30));
  //GameManager::getSinglentonPtr()
 
  _mainTrack = GameManager::getSingletonPtr()->getTrackManager()->load("Space Fighter Loop.mp3");
  //_simpleEffect = GameManager::getSingletonPtr()->getSoundFXManager()->load("nightmare.wav");

  // Reproducción del track principal...
  _mainTrack->play();

  _exitGame = false;
}

void
IntroState::exit()
{
  //if(_mainTrack->isPlaying())
  _mainTrack->stop();

  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
  
}

void
IntroState::pause ()
{
}

void
IntroState::resume ()
{
}
void 
IntroState::quit(){
  _exitGame = true;
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt) 
{
  
  return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
  // Transición al siguiente estado.
  // Espacio --> PlayState
  if (e.key == OIS::KC_SPACE) {
    changeState(PlayState::getSingletonPtr());
  }
}
void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }

 // if(e.key == OIS::KC_LEFT)   axisX = 0; 
 // if(e.key == OIS::KC_RIGHT)  axisX = 0;
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

IntroState*
IntroState::getSingletonPtr ()
{
return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}
