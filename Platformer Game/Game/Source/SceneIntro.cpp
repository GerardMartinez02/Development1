#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"


#include "Defs.h"
#include "Log.h"

SceneIntro::SceneIntro(App* app, bool start_enabled) : Module(app, start_enabled)
{
	startButton = NULL;
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
	LOG("Loading Intro assets");
	bool ret = true;
	//app->audio->PlayMusic("Assets/audio/music/introMusic.ogg");
	
	Application->render->camera.x = app->render->camera.y = 0;

	/*introLogo = Application->tex->Load("Assets/textures/introImage.png");
	startButton = Application->tex->Load("Assets/textures/startButton.png");
	black = Application->tex->Load("Assets/textures/pinballLoading.png");*/
	
	sCounter = 0;
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
	sCounter++;
	delay++;

	app->scene->Disable();
	app->player->Disable();

	
	SDL_Rect rect;

	Application->render->Blit(introLogo, 0, 0, NULL, 1.0f, NULL, 2147483647, 2147483647);

	Application->render->Blit(introLogo, 0, 0, NULL, 1.0f, NULL, 2147483647, 2147483647);

	if ((delay / 30) % 2 == 0)
	{
		Application->render->Blit(startButton, 90, 700, NULL, 1.0f, NULL, 2147483647, 2147483647);
	}

	if (transition == true)
	{
		transitionTimer++;
		Application->render->Blit(black, 0, 0, NULL, 1.0f, NULL, 2147483647, 2147483647);
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		
		if (transition == false)
		{
			transition = true;
		}
		trackID = 1;
	}

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->map->Enable();
		app->scene->Enable();
		app->player->Enable();
		//app->physics->Enable();

		if (transition == false)
		{
			transition = true;
		}

		trackID = 2;
		app->intro->Disable();
	}

	if (transitionTimer > 150)
	{
		if (Application->scene->IsActive() == false)
		{
			Application->scene->Enable();
		}
		if (Application->player->IsActive() == false)
		{
			Application->player->Enable();
		}
		Application->scene->Disable();
	}


	if (transitionTimer > 150) Application->fadeToBlack->FadeToBlack((Module*)Application->intro, (Module*)Application->scene, 90);
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
	app->render->DrawTexture(backgroundIntro, 0, 2080, NULL, 1.0f);
	
	if ((delay / 30) % 2 == 0)
	{
		app->render->DrawTexture(startButton, 100, 2180, NULL, 1.0f);
	}

	return ret;
}

// Called before quitting
bool SceneIntro::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(introLogo);
	app->tex->UnLoad(black);
	app->tex->UnLoad(startButton);
	app->tex->UnLoad(backgroundIntro);
	
	return true;
}



