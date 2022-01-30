#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "Module.h"
#include "Animation.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class GameOver : public Module
{
public:

	GameOver();

	// Destructor
	virtual ~GameOver();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	SDL_Texture* exitButton;
	SDL_Texture* exitButtonTouch;

	GuiButton* exitButtonG;

private:
	SDL_Texture* gameOverImg;
	SDL_Texture* idleBackground;

	int frames = 0;
	SString folder;
	SString audioFile;
};

#endif // _SCENE_H_#pragma once