

#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:

	SceneIntro(App* app, bool start_enabled = true);

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

	int sCounter;
	
private:
	SDL_Texture* introLogo;
	SDL_Texture* startButton;
	SDL_Texture* black;
	SDL_Texture* backgroundIntro;

	int transitionTimer;
	bool transition;

	int delay;
	int trackID;
};

#endif // __SCENE_H__
