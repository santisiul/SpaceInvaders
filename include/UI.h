#ifndef UI_H
#define UI_H

//#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class UI{

 //private:
 	CEGUI::OgreRenderer* renderer;
 public:
	UI(){};
	~UI(){};

	void createGUI(){
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

	  CEGUI::FontManager::getSingleton().createAll("*.font", "Fonts");
	  //Sheet
	  CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex2");

	  //Config Window
	  CEGUI::Window* menu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("menu.layout");
	  
	  
	  CEGUI::Window* exitButton = menu->getChild("ExitButton");
	  
	//  exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
	            // CEGUI::Event::Subscriber(&MyFrameListener::quit, 
	              //      _framelistener));

	  //Attaching buttons
  	sheet->addChild(menu);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

	};

/*
	bool keyPressed(const OIS::KeyEvent& evt);
  	bool keyReleased(const OIS::KeyEvent& evt);
  	bool mouseMoved(const OIS::MouseEvent& evt);
  	bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
  	bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

  	CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
*/



	
};

#endif