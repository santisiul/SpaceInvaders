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

	void createGUI();

	bool quit(const CEGUI::EventArgs &e);
	bool credits(const CEGUI::EventArgs &e);
	bool play(const CEGUI::EventArgs &e);
	bool score(const CEGUI::EventArgs &e);
	bool back(const CEGUI::EventArgs &e);
	bool pause(const CEGUI::EventArgs &e);
	bool finish(const CEGUI::EventArgs &e);
	bool restart(const CEGUI::EventArgs &e);

};

#endif