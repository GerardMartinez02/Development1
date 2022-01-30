#include "pauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "ModulePlayer.h"
#include "GuiManager.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "enemyBird.h"
#include "enemyDragon.h"
#include "Map.h"
#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>


PauseMenu::PauseMenu() : Module()
{
	name.Create("PauseMenu");
}

// Destructor
PauseMenu::~PauseMenu()
{}

// Called before render is available
bool PauseMenu::Awake()
{
	LOG("Loading PauseMenu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool PauseMenu::Start()
{
	titleIntro = app->tex->Load("Assets/scenes/titleImage.png");
	backgroundIntro = app->tex->Load("Assets/scenes/introImage.png");
	startButton = app->tex->Load("Assets/textures/ui/PressEnterToStartRed.png");
	loading = app->tex->Load("Assets/scenes/loadingScreen.png");
	pauseMenuF = app->tex->Load("Assets/scenes/pauseMenuBackground2.png");

	playButton = app->tex->Load("Assets/tectures/ui/StartButtonBlue.png");
	resumeButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	newGameButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	settingsButton = app->tex->Load("Assets/textures/ui/SettingsButtonBlue.png");
	creditsButton = app->tex->Load("Assets/textures/ui/CreditsButtonBlue.png");
	exitButton = app->tex->Load("Assets/textures/ui/exitButtonBlue.png");
	returnButton = app->tex->Load("Assets/textures/ui/XButtonBlue.png");
	button = app->tex->Load("Assets/textures/ui/ButtonBlue.png");

	playButtonTouch = app->tex->Load("Assets/tectures/ui/StartButtonOrange.png");
	resumeButtonTouch = app->tex->Load("Assets/textures/ui/ResumeButtonOrange.png");
	newGameButtonTouch = app->tex->Load("Assets/textures/ui/ResumeButtonOrange.png");
	settingsButtonTouch = app->tex->Load("Assets/textures/ui/SettingsButtonOrange.png");
	creditsButtonTouch = app->tex->Load("Assets/textures/ui/CreditsButtonOrange.png");
	exitButtonTouch = app->tex->Load("Assets/textures/ui/exitButtonOrange.png");
	returnButtonTouch = app->tex->Load("Assets/textures/ui/XButtonOrange.png");
	buttonTouch = app->tex->Load("Assets/textures/ui/ButtonOrange.png");
	
	creditsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, { 215, 2280, 108, 35 }, this, creditsButton, NULL, {});
	exitButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, { 215, 2380, 108, 35 }, this, exitButton, NULL, {});
	returnButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, { 10, 2480, 71, 35 }, this, returnButton, NULL, {});
	settingsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, { 105, 2180, 108, 35 }, this, settingsButton, NULL, {});

	resumeButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, { 105, 160, 108, 35 }, this, resumeButton, NULL, {});
	newGameButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, { 215, 200, 108, 35 }, this, newGameButton, NULL, {});


	fullScreenBoxG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 8, { 185, 149, 17, 17 }, this, fullScreenOff, NULL, {});
	fullScreenBoxSelectedG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, { 20, 140, 161, 9 }, this, fullScreenSelected, NULL, {});

	VSyncBoxG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, { 20,180,213,35 }, this, VSyncOff, NULL, {});


	fxVolumeSliderG = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 11, { 20,60,195,35 }, this, baseSlider_fx, sliderSelector, { 214,70,14,16 });
	musicVolumeSliderG = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 12, { 20,100,195,35 }, this, baseSlider_music, sliderSelector, { 214,110,14,16 });

	pauseTimer = 0;
	noPauseTimer = 0;
	sceneTimer = 0;
	return true;
}

// Called each loop iteration
bool PauseMenu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool PauseMenu::Update(float dt)
{
	sceneTimer++;

	if (app->player->pauseMenu == true)
	{
		pauseTimer++;
		noPauseTimer = 0;

		resumeButtonG->canClick = true;
		settingsButtonG->canClick = true;
		exitButtonG->canClick = true;
		returnButtonG->canClick = false;
		fxVolumeSliderG->canClick = false;
		musicVolumeSliderG->canClick = false;
		fullScreenBoxG->canClick = false;
		fullScreenBoxSelectedG->canClick = false;
		VSyncBoxG->canClick = false;

		if (TitleTransition == true)
		{
			app->sceneIntro->Enable();
			app->sceneIntro->introMenu = true;
			app->player->pauseMenu = false;
			app->map->Disable();
			app->scene->Disable();
			app->player->Disable();
			app->enemyBird->Disable();
			app->fonts->Disable();
			app->pauseMenu->Disable();
			TitleTransition = false;
		}

		if (pauseTimer <= 1) Mix_PauseMusic();

	}
	else
	{
		pauseTimer = 0;
		noPauseTimer++;

		if (noPauseTimer <= 1) Mix_ResumeMusic();
	}
	if (app->player->pauseMenu == false)
	{
		resumeButtonG->canClick = false;
		settingsButtonG->canClick = false;
		exitButtonG->canClick = false;
		returnButtonG->canClick = false;
		fxVolumeSliderG->canClick = false;
		musicVolumeSliderG->canClick = false;
		fullScreenBoxG->canClick = false;
		fullScreenBoxSelectedG->canClick = false;
		VSyncBoxG->canClick = false;
	}

	if (options == true)
	{
		fxVolumeSliderG->canClick = true;
		musicVolumeSliderG->canClick = true;
		fullScreenBoxG->canClick = true;
		fullScreenBoxSelectedG->canClick = false;
		VSyncBoxG->canClick = true;
		returnButtonG->canClick = true;
	}

	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;

	if (app->player->pauseMenu == true)
	{

		app->render->DrawTexture(pauseMenuF, 0, 2080, NULL, 1.0f);
		//app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		if (options == false)
		{
			if (exitButtonG->state == GuiControlState::NORMAL && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButton);
			if (exitButtonG->state == GuiControlState::FOCUSED && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButtonTouch);
			exitButtonG->Draw(app->render);

			if (resumeButtonG->state == GuiControlState::NORMAL && resumeButtonG->canClick == true) resumeButtonG->SetTexture(resumeButton);
			if (resumeButtonG->state == GuiControlState::FOCUSED && resumeButtonG->canClick == true) resumeButtonG->SetTexture(resumeButtonTouch);
			resumeButtonG->Draw(app->render);

			if (settingsButtonG->state == GuiControlState::NORMAL && settingsButtonG->canClick == true) settingsButtonG->SetTexture(settingsButton);
			if (settingsButtonG->state == GuiControlState::FOCUSED && settingsButtonG->canClick == true) settingsButtonG->SetTexture(settingsButtonTouch);
			settingsButtonG->Draw(app->render);

		}
		if (options == true)
		{
			if (returnButtonG->state == GuiControlState::NORMAL && returnButtonG->canClick == true) returnButtonG->SetTexture(returnButton);
			if (returnButtonG->state == GuiControlState::FOCUSED && returnButtonG->canClick == true) returnButtonG->SetTexture(settingsButtonTouch);
			returnButtonG->Draw(app->render);

			fxVolumeSliderG->Draw(app->render);

			musicVolumeSliderG->Draw(app->render);

		}
	}



	return ret;

	return true;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(PauseFrame);

	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(settingsButton);
	app->tex->UnLoad(exitButton);

	app->tex->UnLoad(exitButtonTouch);
	app->tex->UnLoad(resumeButtonTouch);
	app->tex->UnLoad(settingsButtonTouch);
	app->tex->UnLoad(exitButtonTouch);

	app->guiManager->DestroyGuiControl(11);
	app->guiManager->DestroyGuiControl(12);
	app->guiManager->DestroyGuiControl(13);
	app->guiManager->DestroyGuiControl(14);
	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control) {
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 12 && resumeButtonG->canClick == true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			app->player->pauseMenu = false;
		}

		if (control->id == 13 && settingsButtonG->canClick == true)
		{
			//SETTINGS BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			options = true;


		}
		if (control->id == 15 && exitButtonG->canClick == true)
		{
			//EXIT BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			exit(0);

		}
	}

	default: break;
	}

	return true;
}