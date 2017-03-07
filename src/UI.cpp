#include "UI.h"
#include "GameManager.h"
#include "PlayState.h"
#include "IntroState.h"
#include "PauseState.h"

void
UI::createGUI(){
	//CEGUI
	renderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	// Let's make the OS and the CEGUI cursor be in the same place
	CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();  
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(-mousePos.d_x,-mousePos.d_y);
	 
	CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");
	//Sheet
	CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex2");

	//Config Window
	CEGUI::Window* menu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("menu.layout");
	  
		CEGUI::Window* exitButton = menu->getChild("ExitButton");
		  exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::quit, 
		                    this));

		CEGUI::Window* creditsButton = menu->getChild("CreditsButton");
		  creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::credits,
		                    this));

		CEGUI::Window* playButton = menu->getChild("PlayButton");
		  playButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::play,
		                    this));

		CEGUI::Window* scoreButton = menu->getChild("ScoreButton");
		  scoreButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::score,
		                    this));  
	
	CEGUI::Window* credits = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("credits.layout");
	credits->setVisible(false);
		  
		CEGUI::Window* returnCredits = credits->getChild("ReturnButton");
		  returnCredits->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::back,
		                    this));

	CEGUI::Window* game = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("game.layout");
	game->setVisible(false);

		  
		CEGUI::Window* pause = game->getChild("PauseButton");
		  pause->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::pause,
		                    this));

		CEGUI::Window* finish = game->getChild("panel")->getChild("finishButton");
		finish->setVisible(false);
		  finish->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::finish,
		                    this));

		CEGUI::Window* restart = game->getChild("panel")->getChild("restartButton");
		  restart->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::restart,
		                    this));
		  game->getChild("panel")->setVisible(false);

	CEGUI::Window* win = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("win.layout");
	win->setVisible(false);

	 	CEGUI::Window* finishWin = win->getChild("finishButton");
		  finishWin->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::finish,
		                    this));

		CEGUI::Window* restartWin = win->getChild("restartButton");
		  restartWin->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::restart,
		                    this));

	CEGUI::Window* score = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("score.layout");
	score->setVisible(false);

		CEGUI::Window* returnScore = score->getChild("ReturnButton");
		  returnScore->subscribeEvent(CEGUI::PushButton::EventClicked,
		             CEGUI::Event::Subscriber(&UI::back,
		                    this));




	  //Attaching buttons
  	sheet->addChild(menu);
  	sheet->addChild(credits);
 	sheet->addChild(game);
  	sheet->addChild(win);
  	sheet->addChild(score);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

bool UI::quit(const CEGUI::EventArgs &e)
{
	GameManager::getSingletonPtr()->quit();
  // _quit = true;
   return true;
}

bool UI::credits(const CEGUI::EventArgs &e)
{
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  rootWindow->getChildRecursive("menu")->setVisible(false);
  rootWindow->getChildRecursive("credits")->setVisible(true);
  return true;
}
bool UI::score(const CEGUI::EventArgs &e)
{
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  rootWindow->getChildRecursive("menu")->setVisible(false);
  CEGUI::Window* scoreWindow = rootWindow->getChildRecursive("score");
  scoreWindow->setVisible(true);

  // stringstream sstrm; sstrm << "";


  // for (int i = 0; i < file->getGamers(); ++i)
  // {
  //    sstrm << file->getGamer(i) << endl;
  // }
  // //sstrm << "[vert-alignment='top']";
  // cout<<"gamers"<<file->getGamers()<<endl;
  // cout<< sstrm.str() <<endl;;
  // scoreWindow->getChild("text")->setText(sstrm.str());
  return true;
}

bool UI::play(const CEGUI::EventArgs &e)
{
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  rootWindow->getChildRecursive("menu")->setVisible(false);
  rootWindow->getChildRecursive("game")->setVisible(true);

  GameManager::getSingletonPtr()->changeState(PlayState::getSingletonPtr());
  // _camera->setPosition(Ogre::Vector3(0,0,50));
  // _camera->lookAt(Ogre::Vector3(0,0,0));
  // //createCombination(combinationSize);
  // inGame = true;
   return true;
}

bool UI::back(const CEGUI::EventArgs &e)
{
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  rootWindow->getChildRecursive("menu")->setVisible(true);
  rootWindow->getChildRecursive("credits")->setVisible(false);
  rootWindow->getChildRecursive("score")->setVisible(false);

  return true;
}

bool UI::pause(const CEGUI::EventArgs &e)
{
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  CEGUI::Window* gameWindow = rootWindow->getChildRecursive("game");

  CEGUI::Window* panel = gameWindow->getChildRecursive("panel");
  bool show;
  if (panel->isVisible()){ show = false; }
  else{ show = true; }
  
  gameWindow->getChildRecursive("panel")->setVisible(show);
  // GameManager::getSingletonPtr()->pushState(PauseState::getSingletonPtr());

  //gameWindow->getChildRecursive("restartButton")->setVisible(show);

  return true;
}

bool UI::finish(const CEGUI::EventArgs &e)
{
  
  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  rootWindow->getChildRecursive("menu")->setVisible(true);
  rootWindow->getChildRecursive("game")->setVisible(false);

  CEGUI::Window* gameWindow = rootWindow->getChildRecursive("game");
  gameWindow->getChildRecursive("panel")->setVisible(false);

  GameManager::getSingletonPtr()->changeState(IntroState::getSingletonPtr());

  //gameWindow->getChildRecursive("restartButton")->setVisible(false);

  // CEGUI::Window* winWindow = rootWindow->getChildRecursive("win");
  //  string name = winWindow->getChildRecursive("nameEditbox")->getText().c_str();
  //  cout<<"rounds"<<rounds<<endl;
  // if (winWindow->isVisible())
  // {

  //   stringstream sstrm; sstrm << name << " " << rounds << " "<< static_cast<int>(chronometer / 60) << ":" << (static_cast<int>(chronometer) % 60)<<endl;
  //   cout<<sstrm.str()<<endl;
  //   file->addGamer(sstrm.str());
  // }
  // rootWindow->getChildRecursive("win")->setVisible(false);

  // _camera->setPosition(Ogre::Vector3(0,0,50));
  // _camera->lookAt(Ogre::Vector3(0,0,0));

  // initialState();
  // //Ogre::SceneNode* node = static_cast<Ogre::SceneNode*>(_sceneManager->getRootSceneNode()->getChild("back")->getChild("front"));
  // //node->setVisible(false);
  // inGame = false;
  // evaluate = false;

  

  return true;
}

bool UI::restart(const CEGUI::EventArgs &e)
{
  

  CEGUI::Window* rootWindow=  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  CEGUI::Window* gameWindow = rootWindow->getChildRecursive("game");
  gameWindow->getChildRecursive("panel")->setVisible(false);
  // gameWindow->getChildRecursive("restartButton")->setVisible(false);

  rootWindow->getChildRecursive("win")->setVisible(false);

  // initialState();
  // _camera->setPosition(Ogre::Vector3(0,0,50));
  // _camera->lookAt(Ogre::Vector3(0,0,0));
  // inGame = true;
  return true;
}