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
   _sceneMgr->setSkyBox(true, "skybox");

  _loopTrack = GameManager::getSingletonPtr()->getTrackManager()->load("In a Heartbeat.mp3");
  _loopTrack->play();

  _shoot = GameManager::getSingletonPtr()->getSoundFXManager()->load("quonux_shoot.wav");
   _explode = GameManager::getSingletonPtr()->getSoundFXManager()->load("exploding.wav");

   cout<<"playState Enter"<<endl;

  fisics = new Fisics();
  player = new Player();

  player->getNode()->setPosition(Ogre::Vector3(0,0,30));
  fisics->subscribe(player);

  // //Se crea pool de proyectiles
  // for (int i = 0; i < 20; ++i)
  // {
  //   Projectile* projectile = new Projectile();
  //   //projectile->deactivate();
  //   projectile->getNode()->setPosition(Ogre::Vector3(0,0,80));
  //   projectiles.push_back(projectile);
  //   fisics->subscribe(projectile);
  // }

  //coloca a los enemigos
  numEnemies = 30;
  int z = 0;
  int x = 0;
  for (int i = 0; i < numEnemies; ++i)
  {
    if (i%10 == 0){ z-=8; x=0;}
    Enemy* enemy = new Enemy();
    enemy->getNode()->setPosition(Ogre::Vector3(x*4 -20, 0, z));
    Enemies.push_back(enemy);
    fisics->subscribe(enemy);

    x++;
  }

  x=0; z=20;
  for (int i = 0; i < 30; ++i)
  {
    if(i%5 == 0){x+=8;}
    if(i%15 == 0){z+=1; x=0;}
    Wall* wall = new Wall();
    wall->getNode()->setPosition(Ogre::Vector3(x-15, 0, z));
    //Walls.push_back(wall);
    fisics->subscribe(wall);
    x++;
  }
    
  _exitGame = false;
  pts = 0;
  timeScale = 1;
  axisX = 0;
  time = 0;
  chronometer = 0;

  //cout<<"fin play enter";
}

void
PlayState::exit ()
{
  cout<<"PlayState exit"<<endl;
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
   _loopTrack->stop();

  //delete fisics;
  //delete player;
 // / for (std::vector<Enemy*>::iterator i = Enemies.begin(); i != Enemies.end(); ++i)
 //  {
 //    delete (*i);
 //   }
   Enemies.clear();
 //   for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
 //   {
 //     delete (*i);
 //   }
   projectiles.clear();

}

void
PlayState::pause()
{ 
  //pushState(PauseState::getSingletonPtr());
  timeScale = 0;
  _loopTrack->pause();
}

void
PlayState::resume()
{
  timeScale = 1;
  _loopTrack->play();
}

void 
PlayState::quit(){
  _exitGame = true;
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{

  deltaT = evt.timeSinceLastFrame * timeScale;
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
    fisics->calculateCollisions();  
  
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
    pause();
  }


  if(e.key == OIS::KC_LEFT)   axisX = -1; 
  if(e.key == OIS::KC_RIGHT)  axisX = 1;

  if(e.key == OIS::KC_SPACE){
   // _shoot->play();

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
    
    _shoot->play();
    //_explode->play();

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
      fisics->subscribe(bullet);
    }

    bullet->start(shooter);
   
}


void PlayState::soundExplode(){
  _explode->play();
}

void PlayState::destroyEnemy(){
  numEnemies--;
  if (numEnemies == 0)
  {
    GameManager::getSingletonPtr()->ui->winner(true);
    timeScale = 0;
  }
  pts += 100;
  //instroducir puntos en gui
  stringstream sstr; sstr << pts << " pts";
  GameManager::getSingletonPtr()->ui->setScore(sstr.str());
}

void PlayState::lose(){
  GameManager::getSingletonPtr()->ui->winner(false);
  timeScale = 0;
  //pause();
}