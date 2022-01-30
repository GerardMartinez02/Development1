#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class PauseMenu : public Module
{
public:

	PauseMenu();

	// Destructor
	virtual ~PauseMenu();

	// Called before render is available
	bool Awake();

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

	bool OnGuiMouseClickEvent(GuiControl* control);

	int buttonClickedFx = 0;
	int sceneTimer;
	int pauseTimer;
	int noPauseTimer;
	bool options = false;
	bool TitleTransition = false;


private:

	SDL_Texture* PauseFrame;

	SDL_Texture* startButton;
	SDL_Texture* titleIntro;
	SDL_Texture* backgroundIntro;
	SDL_Texture* loading;

	//Menu Buttons
	SDL_Texture* playButton;
	SDL_Texture* resumeButton;
	SDL_Texture* resumeButtonOff;
	SDL_Texture* newGameButton;
	SDL_Texture* settingsButton;
	SDL_Texture* creditsButton;
	SDL_Texture* returnButton;
	SDL_Texture* exitButton;
	SDL_Texture* pauseMenuF;
	SDL_Texture* button;

	SDL_Texture* playButtonTouch;
	SDL_Texture* resumeButtonTouch;
	SDL_Texture* resumeButtonOffTouch;
	SDL_Texture* newGameButtonTouch;
	SDL_Texture* settingsButtonTouch;
	SDL_Texture* creditsButtonTouch;
	SDL_Texture* returnButtonTouch;
	SDL_Texture* exitButtonTouch;
	SDL_Texture* buttonTouch;

	GuiButton* playButtonG;
	GuiButton* resumeButtonG;
	GuiButton* resumeButtonGOff;
	GuiButton* newGameButtonG;
	GuiButton* settingsButtonG;
	GuiButton* creditsButtonG;
	GuiButton* returnButtonG;
	GuiButton* exitButtonG;
	GuiButton* buttonG;


	//CheckBox
	SDL_Texture* fullScreenOn;
	SDL_Texture* fullScreenOff;
	SDL_Texture* VSyncOn;
	SDL_Texture* VSyncOff;

	SDL_Texture* fullScreenOnTouch;
	SDL_Texture* fullScreenOffTouch;
	SDL_Texture* VSyncOnTouch;
	SDL_Texture* VSyncOffTouch;

	SDL_Texture* fullScreenSelected;

	GuiCheckBox* VSyncBoxG;
	GuiCheckBox* fullScreenBoxG;
	GuiCheckBox* fullScreenBoxSelectedG;

	//Sliders
	SDL_Texture* baseSlider_fx;
	SDL_Texture* baseSlider_music;

	SDL_Texture* sliderSelector;
	SDL_Texture* sliderSelectorOnIdle;
	SDL_Texture* sliderSelectorPressed;

	GuiSlider* musicVolumeSliderG;
	GuiSlider* fxVolumeSliderG;
};

#endif // __SCENE_FOREST_H__
#pragma once
