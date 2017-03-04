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

  fisics = new Fisics();
  //parent = new Enemy();
  player = new Player();
  player->getNode()->setPosition(Ogre::Vector3(0,0,30));

  fisics->subscribe(player);

  for (int i = 0; i < 20; ++i)
  {
    Projectile* projectile = new Projectile();
    //projectile->deactivate();
    projectile->getNode()->setPosition(Ogre::Vector3(0,0,80));
    projectiles.push_back(projectile);
    fisics->subscribe(projectile);
  }

  int z = 0;
  int x = 0;
  for (int i = 0; i < 30; ++i)
  {
    if (i%10 == 0){ z-=7; x=0;}
   // cout<<x;
    Enemy* enemy = new Enemy();
    enemy->getNode()->setPosition(Ogre::Vector3(x*3 -15, 0, z));
    Enemies.push_back(enemy);
    fisics->subscribe(enemy);

    x++;
  }
    
  _exitGame = false;
  axisX = 0;
  time = 0;
  chronometer = 0;

  //cout<<"fin play enter";
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
  deltaT = evt.timeSinceLastFrame;
  time *= deltaT;

  if(axisX != 0)
    player->update(axisX, deltaT);

  //Actualiza posiciones de los enemigos
  for (std::vector<Enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); ++i)
  {
    (*i)->update(deltaT);
  }

  //Actualiza posiciones de los projectiles
  for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
  {
    if ((*i)->isActive()) { (*i)->update(deltaT); } 
  }

  chronometer += deltaT;
  if (chronometer > 2)
  {
    int random = Ogre::Math::RangeRandom(1, Enemies.size());
    Enemy* enemy = Enemies[random];
    if( enemy->isActive() && enemy->shoot(player->getNode()->getPosition())){

      shootProjectile(enemy);
      chronometer = 0;
    }
  }
  
 
  //Calcula colisiones de objetos
  //if(chronometer > 1){
    fisics->calculateCollisions();
   // chronometer = 0;
  //}
  
  
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
    shootProjectile(player);
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

void PlayState::shootProjectile(GameObject* shooter){
    
    bool empty = true;
    Projectile* bullet;

    for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
    {
      if(!(*i)->isActive()){
        bullet =  (*i);
        empty = false;
        break;
      }      
    }
    
    if (empty)
    {
      bullet = new Projectile();
      projectiles.push_back(bullet);
    }

    bullet->start(shooter);
   
}