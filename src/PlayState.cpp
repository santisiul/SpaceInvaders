#include "PlayState.h"
#include "PauseState.h"

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  // Se recupera el gestor de escena y la cámara.
  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("IntroCamera");
  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  // Nuevo background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  parent = new Enemy();
  player = new Player();
  player->getNode()->setPosition(Ogre::Vector3(0,0,30));

  int z = 0;
  int x = 0;
  for (int i = 0; i < 10; ++i)
  {
    if (i%5 == 0){ z-=8; x=0;}
    cout<<x;
    
    //ostringstream sstrm; sstrm<<"enemy"<<i;
    Enemy* enemy = new Enemy(parent->getNode());
    enemy->getNode()->setPosition(Ogre::Vector3(x*3 -6, 0, z));
    Enemies.push_back(enemy);

    x++;
  }

  for (int i = 0; i < 5; ++i)
  {
    Projectile* projectile = new Projectile();
    projectile->deactivate();
    projectile->getNode()->setPosition(Ogre::Vector3(0,0,80));
    projectiles.push_back(projectile);
  }
    
  _exitGame = false;
  axisX = 0;
}

void
PlayState::exit ()
{
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
}

void
PlayState::resume()
{
  // Se restaura el background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  if(axisX != 0)
    player->update(axisX);

  parent->update();

  for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
  {
    if ((*i)->isActive()) { (*i)->update(); } 
  }
  cout<<endl;
  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{
  // Tecla p --> PauseState.
  if (e.key == OIS::KC_P) {
    pushState(PauseState::getSingletonPtr());
  }

  if(e.key == OIS::KC_LEFT)   axisX = -1; 
  if(e.key == OIS::KC_RIGHT)  axisX = 1;

  if(e.key == OIS::KC_SPACE){
    bool empty = true;
    Ogre::Vector3 pos = player->getNode()->getPosition();
    for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
    {
      if(!(*i)->isActive()){
        (*i)->getNode()->setPosition(pos);
        (*i)->activate();
        empty = false;
        break;
      }      
    }
    if (empty)
    {
      Projectile* projectile = new Projectile();
      projectiles.push_back(projectile);
      projectile->getNode()->setPosition(pos);
      projectile->activate();
    }

  }
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }

  if(e.key == OIS::KC_LEFT)   axisX = 0; 
  if(e.key == OIS::KC_RIGHT)  axisX = 0;
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}