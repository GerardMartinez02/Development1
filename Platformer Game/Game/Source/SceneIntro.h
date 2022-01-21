

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
	bool nextImage;
	bool introMenu;

	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitRequested;

	bool SavedGame;

	iPoint position;
	
private:
	SDL_Texture* startButton;
	SDL_Texture* titleIntro;
	SDL_Texture* backgroundIntro;
	SDL_Texture* loading;
	
	SDL_Texture* playButton;
	SDL_Texture* resumeButton;
	GuiButton* resumeButtonOff;
	SDL_Texture* newGameButton;
	SDL_Texture* settingsButton;
	SDL_Texture* creditsButton;
	SDL_Texture* returnButton;
	SDL_Texture* exitButton;

	GuiButton* playButtonG;
	GuiButton* resumeButtonG;
	GuiButton* resumeButtonGOff;
	GuiButton* newGameButtonG;
	GuiButton* settingsButtonG;
	GuiButton* creditsButtonG;
	GuiButton* returnButtonG;
	GuiButton* exitButtonG;
};

#endif // __SCENE_H__
