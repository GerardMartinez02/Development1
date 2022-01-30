

#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"
#include "Animation.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:

	SceneIntro();

	// Destructor
	virtual ~SceneIntro();

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

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;


	
	int sCounter;
	int delay;
	int delaySaved;
	bool nextImage;
	bool nextImageSaved;


	bool introMenu = false;
	bool options = false;
	bool credits = false;

	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

	bool SavedGame;

	int buttonClickedFx = 0;
	int buttonNotClickedFx = 0;

	bool titleScreenWait = true;

	bool Vsync = false;
	bool FullScreen = false;

	iPoint position;
	
private:
	
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

	SDL_Texture* baseSlider_fxTouch;
	SDL_Texture* baseSlider_musicTouch;

	SDL_Texture* sliderSelector;
	SDL_Texture* sliderSelectorTouch;

	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;

	

	
};

#endif // __SCENE_H__
