#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneIntro.h"
#include "ModuleFadeToBlack.h"


#include "Defs.h"
#include "Log.h"

SceneIntro::SceneIntro() : Module()
{
	
}

// Destructor
SceneIntro::~SceneIntro()
{}

// Called before render is available
bool SceneIntro::Awake(pugi::xml_node& config)
{
	LOG("Loading Intro");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool SceneIntro::Start()
{
	// L03: DONE: Load map
	app->audio->PlayMusic("Assets/audio/music/introMusic.ogg");
	backgroundIntro = app->tex->Load("Assets/maps/backgroundIntro.png");
	startButton = app->tex->Load("Assets/textures/startButton.png");

	delay = 0;

	return true;
}

// Called each loop iteration
bool SceneIntro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneIntro::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
	}	
	return true;
}

// Called each loop iteration
bool SceneIntro::PostUpdate()
{
	bool ret = true;
	delay++;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}
	app->render->DrawTexture(backgroundIntro, 0, 0, NULL, 1.0f);
	
	if ((delay / 30) % 2 == 0)
	{
		app->render->DrawTexture(startButton, 0, 0, NULL, 1.0f);
	}

	return ret;
}

// Called before quitting
bool SceneIntro::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(backgroundIntro);
	app->tex->UnLoad(startButton);
	return true;
}



