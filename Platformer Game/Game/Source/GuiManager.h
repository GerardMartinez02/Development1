#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"

#include "List.h"

class GuiManager : public Module
{
public:

	GuiManager();

	virtual ~GuiManager();

	bool Start();

	bool Update(float dt);

	bool Draw();

	bool CleanUp();

	GuiControl* CreateGuiControl(GuiControlType type, int id, SDL_Rect bounds, Module* observer, SDL_Texture* texture, SDL_Texture* sliderTexture, SDL_Rect sliderBounds = { 0,0,0,0 });

	void DestroyGuiControl(int id);

	void AddGuiControl(int id);

	bool UpdateAll(float dt, bool logic);

public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
	int id = 0;
	SDL_Texture* sceneIntro;
};

#endif

