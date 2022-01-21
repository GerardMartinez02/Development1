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
#include "GuiManager.h"

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

	playButton = app->tex->Load("Assets/tectures/ui/StartButtonBlue.png");
	resumeButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	newGameButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	settingsButton = app->tex->Load("Assets/textures/ui/SettingsButtonBlue.png");
	creditsButton = app->tex->Load("Assets/textures/ui/CreditsButtonBlue.png");
	exitButton = app->tex->Load("Assets/textures/ui/exitButtonBlue.png");
	returnButton = app->tex->Load("Assets/textures/ui/XButtonBlue.png");

	app->render->camera.x = app->map->MapToWorld(0, -130).x;
	app->render->camera.y = app->map->MapToWorld(0, -130).y;


	sCounter = 0;
	delay = 0;
	nextImage = false;
	introMenu = false;

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	playButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, { 120, 2080, 108, 35 }, this); 
	settingsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, { 105, 2180, 108, 35 }, this);
	creditsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, { 215, 2280, 108, 35 }, this);
	exitButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, { 215, 2380, 108, 35 }, this);
	returnButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, { 10, 2480, 71, 35 }, this);

	resumeButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, { 105, 160, 108, 35 }, this);
	newGameButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, { 215, 200, 108, 35 }, this);

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

		playButtonG->Update(dt);
		resumeButtonG->Update(dt);
		newGameButtonG->Update(dt);
		settingsButtonG->Update(dt);
		creditsButtonG->Update(dt);
		exitButtonG->Update(dt);
		returnButtonG->Update(dt);
	}

	if (introMenu == true && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//START BUTTON
		if (playButtonG->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(playButtonG);
		}
		//CONTINUE BUTTON
		if (resumeButtonG->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(resumeButtonG);
		}
		//SETTINGS BUTTON
		if (settingsButtonG->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(settingsButtonG);
		}
		//CREDITS BUTTON
		if (creditsButtonG->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(creditsButtonG);
		}
		//EXIT BUTTON
		if (exitButtonG->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(exitButtonG);
		}
		
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
	
	playButtonG->SetTexture(startButton);
	if (SavedGame == true) newGameButtonG->SetTexture(newGameButton);
	/*if (SavedGame == false) resumeButtonG->SetTexture(resumeButtonOff);*/
	settingsButtonG->SetTexture(settingsButton);
	creditsButtonG->SetTexture(creditsButton);
	exitButtonG->SetTexture(exitButton);
	returnButtonG->SetTexture(returnButton);

	if (introMenu == true)
	{
		app->render->DrawTexture(backgroundIntro, 0, 2080, NULL, 1.0f);

		playButtonG->Draw(app->render);
		resumeButtonG->Draw(app->render);
		settingsButtonG->Draw(app->render);
		creditsButtonG->Draw(app->render);
		exitButtonG->Draw(app->render);

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

	app->tex->UnLoad(playButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(settingsButton);
	app->tex->UnLoad(creditsButton);
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(returnButton);
	return true;
}

bool SceneIntro::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
		switch (control->id)
		{
		case 1:
			app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
			break;
		case 2:
			app->scene->loaded = true;
			app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
			break;
		case 3:
			app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
			break;
		/*case 4:
			app->fadeToBlack->FadeToBlack(this, (Module*)app->titlesettingsScreen);
			break;
		case 5:
			app->fadeToBlack->FadeToBlack(this, (Module*)app->creditsScreen);
			break; */
		case 6:
			exitRequested = true;
			break;
		default:
			break;
		}
	default:
		break;
	}

	return true;
}

bool SceneIntro::LoadState(pugi::xml_node& data)
{
	SavedGame = data.child("saved_game").attribute("bool").as_bool();

	return true;
}

bool SceneIntro::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node savedGame = data.append_child("saved_game");

	savedGame.append_attribute("bool") = SavedGame;

	return true;
}


