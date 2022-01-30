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
#include "ModuleFonts.h"
#include "GuiSlider.h"

#include <iostream>

using namespace std;

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

	playButton = app->tex->Load("Assets/textures/ui/StartButtonBlue.png");
	resumeButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	newGameButton = app->tex->Load("Assets/textures/ui/ResumeButtonBlue.png");
	settingsButton = app->tex->Load("Assets/textures/ui/SettingsButtonBlue.png");
	creditsButton = app->tex->Load("Assets/textures/ui/CreditsButtonBlue.png");
	exitButton = app->tex->Load("Assets/textures/ui/exitButtonBlue.png");
	returnButton = app->tex->Load("Assets/textures/ui/XButtonBlue.png");
	button = app->tex->Load("Assets/textures/ui/ButtonBlue.png");
	/*fullScreenOn = app->tex->Load("Assets/textures/ui/.png");*/
	sliderSelector = app->tex->Load("Assets/textures/ui/ButtonBlue.png");


	playButtonTouch = app->tex->Load("Assets/textures/ui/StartButtonOrange.png");
	resumeButtonTouch = app->tex->Load("Assets/textures/ui/ResumeButtonOrange.png");
	newGameButtonTouch = app->tex->Load("Assets/textures/ui/ResumeButtonOrange.png");
	settingsButtonTouch = app->tex->Load("Assets/textures/ui/SettingsButtonOrange.png");
	creditsButtonTouch = app->tex->Load("Assets/textures/ui/CreditsButtonOrange.png");
	exitButtonTouch = app->tex->Load("Assets/textures/ui/exitButtonOrange.png");
	returnButtonTouch = app->tex->Load("Assets/textures/ui/XButtonOrange.png");
	buttonTouch = app->tex->Load("Assets/textures/ui/ButtonOrange.png");
	sliderSelectorTouch = app->tex->Load("Assets/textures/ui/ButtonOrange.png");

	app->render->camera.x = app->map->MapToWorld(0, -130).x;
	app->render->camera.y = app->map->MapToWorld(0, -130).y;


	sCounter = 0;
	delay = 0;
	nextImage = false;
	introMenu = false;

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	playButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, { 240, 210, 150, 35 }, this, playButton, NULL, {});
	settingsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, { 320, 300, 108, 35 }, this, settingsButton, NULL, {});
	creditsButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, { 130, 300, 108, 35 }, this, creditsButton, NULL, {});
	exitButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, { 10, 10, 108, 35 }, this, exitButton, NULL, {});
	returnButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 7, { 700, 300, 71, 35 }, this, returnButton, NULL, {});

	resumeButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, { 150, 350, 108, 35 }, this, resumeButton, NULL, {});
	newGameButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, { 350, 350, 108, 35 }, this, newGameButton, NULL, {});


	fullScreenBoxG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 8, { 185, 149, 17, 17 }, this, fullScreenOff, NULL, {});
	fullScreenBoxSelectedG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, { 20, 140, 161, 9 }, this, fullScreenSelected, NULL, {});

	VSyncBoxG = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, { 20,180,213,35 }, this, VSyncOff, NULL, {});


	fxVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 11, { 20,60,195,35 }, this, baseSlider_fx, sliderSelector, { 214,70,14,16 });
	musicVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 12, { 20,100,195,35 }, this, baseSlider_music, sliderSelector, { 214,110,14,16 });
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

		playButtonG->canClick = true;
		resumeButtonG->canClick = true;
		newGameButtonG->canClick = true;
		settingsButtonG->canClick = true;
		creditsButtonG->canClick = true;
		exitButtonG->canClick = true;
		returnButtonG->canClick = true;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenBoxG->canClick = false;
		fullScreenBoxSelectedG->canClick = false;
		VSyncBoxG->canClick = false;
	}

	if (options == true)
	{
		playButtonG->canClick = false;
		resumeButtonG->canClick = false;
		newGameButtonG->canClick = false;
		settingsButtonG->canClick = false;
		creditsButtonG->canClick = false;
		exitButtonG->canClick = false;
		returnButtonG->canClick = true;
		fxVolumeSlider->canClick = true;
		musicVolumeSlider->canClick = true;
		fullScreenBoxG->canClick = true;
		fullScreenBoxSelectedG->canClick = true;
		VSyncBoxG->canClick = true;

	}
	if (credits == true)
	{
		playButtonG->canClick = false;
		resumeButtonG->canClick = false;
		newGameButtonG->canClick = false;
		settingsButtonG->canClick = false;
		creditsButtonG->canClick = false;
		exitButtonG->canClick = false;
		returnButtonG->canClick = true;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenBoxG->canClick = false;
		fullScreenBoxSelectedG->canClick = false;
		VSyncBoxG->canClick = false;
	}

	if (introMenu == true && playButtonG->state == GuiControlState::SELECTED && playButtonG->canClick == true)
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
		/*app->pauseMenu->Enable();*/
		app->fonts->Enable();
		app->tex->Enable();

		app->player->score = 0;
		app->player->playerHealth = 75;
		/*app->enemies->Enable();*/
		//app->physics->Enable();

		app->intro->Disable();
	}

	if (nextImageSaved == true) delaySaved++;

	if (delaySaved > 90 && delaySaved <= 91)
	{
		app->map->Enable();
		app->scene->Enable();
		app->player->Enable();
		app->enemyBird->Enable();
		app->enemyDragon->Enable();
		app->coins->Enable();
		/*app->pauseMenu->Enable();*/
		app->fonts->Enable();
		app->tex->Enable();
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
	

	////START BUTTON
		//if (playButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(playButtonG);
		//}
		////CONTINUE BUTTON
		//if (resumeButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(resumeButtonG);
		//}
		////SETTINGS BUTTON
		//if (settingsButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(settingsButtonG);
		//}
		////CREDITS BUTTON
		//if (creditsButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(creditsButtonG);
		//}
		////EXIT BUTTON
		//if (exitButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(exitButtonG);
		//}







	if (introMenu == true)
	{
		app->render->DrawTexture(backgroundIntro, 0, 2080, NULL, 1.0f);

		////START BUTTON
		//if (playButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(playButtonG);
		//}
		////CONTINUE BUTTON
		//if (resumeButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(resumeButtonG);
		//}
		////SETTINGS BUTTON
		//if (settingsButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(settingsButtonG);
		//}
		////CREDITS BUTTON
		//if (creditsButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(creditsButtonG);
		//}
		////EXIT BUTTON
		//if (exitButtonG->state == GuiControlState::PRESSED)
		//{
		//	OnGuiMouseClickEvent(exitButtonG);
		//}

		//playButtonG->SetTexture(playButton);
		//if (SavedGame == true) newGameButtonG->SetTexture(newGameButton);
		///*if (SavedGame == false) resumeButtonG->SetTexture(resumeButtonOff);*/
		//settingsButtonG->SetTexture(settingsButton);
		//creditsButtonG->SetTexture(creditsButton);
		//exitButtonG->SetTexture(exitButton);
		//returnButtonG->SetTexture(returnButton);

		//playButtonG->Draw(app->render);
		//resumeButtonG->Draw(app->render);
		//settingsButtonG->Draw(app->render);
		//creditsButtonG->Draw(app->render);
		//exitButtonG->Draw(app->render);



		if (playButtonG->state == GuiControlState::NORMAL && playButtonG->canClick == true) playButtonG->SetTexture(playButton);
		if (playButtonG->state == GuiControlState::FOCUSED && playButtonG->canClick == true) playButtonG->SetTexture(playButtonTouch);
		playButtonG->Draw(app->render);

		if (SavedGame == true)
		{
			if (resumeButtonG->state == GuiControlState::NORMAL && resumeButtonG->canClick == true) resumeButtonG->SetTexture(resumeButton);
			if (resumeButtonG->state == GuiControlState::FOCUSED && resumeButtonG->canClick == true) resumeButtonG->SetTexture(resumeButtonTouch);
			resumeButtonG->Draw(app->render);
		}
		if (SavedGame == false)
		{
			resumeButtonG->SetTexture(resumeButtonOff);
			resumeButtonG->Draw(app->render);
		}

		if (settingsButtonG->state == GuiControlState::NORMAL && settingsButtonG->canClick == true) settingsButtonG->SetTexture(settingsButton);
		if (settingsButtonG->state == GuiControlState::FOCUSED && settingsButtonG->canClick == true) settingsButtonG->SetTexture(settingsButtonTouch);
		settingsButtonG->Draw(app->render);

		if (creditsButtonG->state == GuiControlState::NORMAL && creditsButtonG->canClick == true) creditsButtonG->SetTexture(creditsButton);
		if (creditsButtonG->state == GuiControlState::FOCUSED && creditsButtonG->canClick == true) creditsButtonG->SetTexture(creditsButtonTouch);
		creditsButtonG->Draw(app->render);

		if (exitButtonG->state == GuiControlState::NORMAL && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButton);
		if (exitButtonG->state == GuiControlState::FOCUSED && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButtonTouch);
		exitButtonG->Draw(app->render);
	}
	if (options == true)
	{
		if (returnButtonG->state == GuiControlState::NORMAL && returnButtonG->canClick == true) returnButtonG->SetTexture(returnButton);
		if (returnButtonG->state == GuiControlState::FOCUSED && returnButtonG->canClick == true) returnButtonG->SetTexture(returnButtonTouch);
		returnButtonG->Draw(app->render);

		fxVolumeSlider->Draw(app->render);

		musicVolumeSlider->Draw(app->render);


		fullScreenBoxSelectedG->SetTexture(fullScreenSelected);
		fullScreenBoxSelectedG->Draw(app->render);

		if (FullScreen == false) fullScreenBoxG->SetTexture(fullScreenOff);
		if (FullScreen == true) fullScreenBoxG->SetTexture(fullScreenOn);
		fullScreenBoxG->Draw(app->render);

		if (Vsync == false) VSyncBoxG->SetTexture(VSyncOff);
		if (Vsync == true) VSyncBoxG->SetTexture(VSyncOn);
		VSyncBoxG->Draw(app->render);

	}
	if (credits == true)
	{
		/*app->render->DrawTexture2(creditsScene, 0, 0, NULL);*/

		if (returnButtonG->state == GuiControlState::NORMAL && returnButtonG->canClick == true) returnButtonG->SetTexture(returnButton);
		if (returnButtonG->state == GuiControlState::FOCUSED && returnButtonG->canClick == true) returnButtonG->SetTexture(returnButtonTouch);
		returnButtonG->Draw(app->render);
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
	/*app->tex->UnLoad(creditsScene);*/

	app->tex->UnLoad(playButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(resumeButtonOff);
	app->tex->UnLoad(settingsButton);
	app->tex->UnLoad(creditsButton);
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(returnButton);
	app->tex->UnLoad(sliderSelector);
	
	app->tex->UnLoad(fullScreenSelected);
	app->tex->UnLoad(sliderSelector);
	app->tex->UnLoad(baseSlider_fx);
	app->tex->UnLoad(baseSlider_music);

	app->tex->UnLoad(playButtonTouch);
	app->tex->UnLoad(resumeButtonTouch);
	app->tex->UnLoad(resumeButtonOff);
	app->tex->UnLoad(settingsButtonTouch);
	app->tex->UnLoad(creditsButtonTouch);
	app->tex->UnLoad(exitButtonTouch);
	app->tex->UnLoad(returnButtonTouch);
	app->tex->UnLoad(sliderSelectorTouch);

	app->guiManager->DestroyGuiControl(1);
	app->guiManager->DestroyGuiControl(2);
	app->guiManager->DestroyGuiControl(3);
	app->guiManager->DestroyGuiControl(4);
	app->guiManager->DestroyGuiControl(5);
	app->guiManager->DestroyGuiControl(6);
	app->guiManager->DestroyGuiControl(7);
	app->guiManager->DestroyGuiControl(8);
	app->guiManager->DestroyGuiControl(9);
	app->guiManager->DestroyGuiControl(10);
	app->guiManager->DestroyGuiControl(11);
	return true;
}

bool SceneIntro::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (control->id == 1 && playButtonG->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			nextImage = true;
		}

		if (control->id == 2 && resumeButtonG->canClick == true)
		{
			if (SavedGame == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				app->audio->PlayFx(buttonClickedFx, 0);
				nextImageSaved = true;
			}
			if (SavedGame == false)
			{
				app->audio->PlayFx(buttonNotClickedFx, 0);
			}
		}
		if (control->id == 3 && settingsButtonG->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			cout << "control->id 3 registered" << endl;
			introMenu = false;
			options = true;
		}

		if (control->id == 4 && creditsButtonG->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);

			introMenu = false;
			credits = true;
		}
		if (control->id == 5 && exitButtonG->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			exit(0);
		}
		if (control->id == 6 && returnButtonG->canClick == true)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			/*app->SaveGameAudio();*/
			options = false;
			credits = false;
			introMenu = true;
		}


	}
	
	case GuiControlType::SLIDER:
	{
		if (control->id == 7 && fxVolumeSlider->canClick == true)
		{

			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.9f) && control->limitBounds.x < control->bounds.x + control->bounds.w)
			{
				app->audio->SliderFX = 90;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.8f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.9f))
			{
				app->audio->SliderFX = 80;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.7f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.8f))
			{
				app->audio->SliderFX = 70;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.6f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.7f))
			{
				app->audio->SliderFX = 60;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.5f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.6f))
			{
				app->audio->SliderFX = 50;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.4f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.5f))
			{
				app->audio->SliderFX = 40;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.3f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.4f))
			{
				app->audio->SliderFX = 30;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.2f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.3f))
			{
				app->audio->SliderFX = 20;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.1f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.2f))
			{
				app->audio->SliderFX = 10;
			}
			if (control->limitBounds.x > control->bounds.x && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.1f))
			{
				app->audio->SliderFX = 0;
			}

		}

		if (control->id == 8 && musicVolumeSlider->canClick == true)
		{

			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.9f) && control->limitBounds.x < control->bounds.x + control->bounds.w)
			{
				app->audio->SliderMusic = 90;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.8f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.9f))
			{
				app->audio->SliderMusic = 80;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.7f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.8f))
			{
				app->audio->SliderMusic = 70;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.6f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.7f))
			{
				app->audio->SliderMusic = 60;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.5f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.6f))
			{
				app->audio->SliderMusic = 50;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.4f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.5f))
			{
				app->audio->SliderMusic = 40;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.3f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.4f))
			{
				app->audio->SliderMusic = 30;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.2f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.3f))
			{
				app->audio->SliderMusic = 20;
			}
			if (control->limitBounds.x > control->bounds.x + (control->bounds.w * 0.1f) && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.2f))
			{
				app->audio->SliderMusic = 10;
			}
			if (control->limitBounds.x > control->bounds.x && control->limitBounds.x < control->bounds.x + (control->bounds.w * 0.1f))
			{
				app->audio->SliderMusic = 0;
			}
		}

	}
	case GuiControlType::CHECKBOX:
	{
		if (control->id == 9 && fullScreenBoxG->canClick == true)
		{
			FullScreen = !FullScreen;
			cout << "control->id 9 registered" << endl;
		}
		if (control->id == 10 && fullScreenBoxSelectedG->canClick == true)
		{
			// Do nothing it is just decoration
		}
		if (control->id == 11 && VSyncBoxG->canClick == true)
		{
			Vsync = !Vsync;
		}
	}
	default: break;
	}

	return true;

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


