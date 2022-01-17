#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "ModuleFadeToBlack.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "Defs.h"
#include "Log.h"
#include "enemyBird.h"
#include "enemyDragon.h"
#include "Coins.h"
#include "GameOver.h"

SceneIntro::SceneIntro() : Module()
{
	name.Create("sceneIntro");
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
	//app->audio->PlayMusic("Assets/audio/music/introMusic.ogg");
	titleIntro = app->tex->Load("Assets/scenes/titleImage.png");
	backgroundIntro = app->tex->Load("Assets/scenes/introImage.png");
	startButton = app->tex->Load("Assets/textures/ui/PressEnterToStartRed.png");
	loading = app->tex->Load("Assets/scenes/loadingScreen.png");

	app->render->camera.x = app->map->MapToWorld(0, -130).x;
	app->render->camera.y = app->map->MapToWorld(0, -130).y;


	sCounter = 0;
	delay = 0;
	nextImage = false;
	introMenu = false;

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
	//->sceneIntro->Enable();
	//app->intro->Enable();
	app->scene->Disable();
	app->player->Disable();
	app->enemyBird->Disable();
	app->enemyDragon->Disable();
	app->coins->Disable();
	app->gameOver->Disable();
	
	sCounter++;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		introMenu = true;
	}

	if (introMenu == true && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		nextImage = true;
		introMenu = false;
		app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
	}

	if (nextImage == true) delay++;

	if (delay > 90 && delay <= 91)
	{
		app->map->Enable();
		app->scene->Enable();
		app->player->Enable();
		app->enemyBird->Enable();
		app->enemyDragon->Enable();
		app->coins->Enable();
		/*app->enemies->Enable();*/
		//app->physics->Enable();

		app->intro->Disable();
	}

	return true;
}

// Called each loop iteration
bool SceneIntro::PostUpdate()
{
	bool ret = true;
	
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}
	app->render->DrawTexture(titleIntro, 0, 2080, NULL, 1.0f);
	
	if (introMenu == true)
	{
		app->render->DrawTexture(backgroundIntro, 0, 2080, NULL, 1.0f);
	}
	
	if ((sCounter / 55) % 2 == 0 && introMenu == false)
	{
		app->render->DrawTexture(startButton, -40, 2200, NULL, 1.0f);
	}

	if(nextImage == true) app->render->DrawTexture(loading, 0, 2080, NULL);

	return ret;
}

// Called before quitting
bool SceneIntro::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(titleIntro);
	app->tex->UnLoad(backgroundIntro);
	app->tex->UnLoad(startButton);
	app->tex->UnLoad(loading);
	return true;
}



