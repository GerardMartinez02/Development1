#include "GameOver.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "Defs.h"
#include "Log.h"
#include "SceneIntro.h"
#include "Coins.h"
#include "enemyBird.h"
#include "enemyDragon.h"
#include "ModuleFonts.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

GameOver::GameOver()
{
	name.Create("gameOver");
}

// Destructor
GameOver::~GameOver()
{}

// Called before render is available
bool GameOver::Awake(pugi::xml_node& config)
{
	LOG("Loading Death");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool GameOver::Start()
{
	gameOverImg = app->tex->Load("Assets/scenes/gameOver.png");
	idleBackground = app->tex->Load("Assets/scenes/idleBackground.png");
	
	exitButton = app->tex->Load("Assets/textures/ui/exitButtonBlue.png");
	exitButtonTouch = app->tex->Load("Assets/textures/ui/exitButtonOrange.png");

	/*app->map->Disable();
	app->sceneIntro->Disable();
	
	app->player->Disable();*/
	
	app->render->camera.x = app->map->MapToWorld(0, -130).x;
	app->render->camera.y = app->map->MapToWorld(0, -130).y;

	//app->render->camera.x = app->render->camera.y = 0;
	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{
	bool ret = true;
	/*if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (app->player->health <= 0)
		{
			app->fadeToBlack->FadeToBlack(this, (Module*)app->scene);
		}
			
		
	}*/
	exitButtonG = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, { 10, 10, 108, 35 }, this, exitButton, NULL, {});
	
	exitButtonG->canClick = true;


	app->player->Disable();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->gameOver->Disable();

		app->intro->Enable();
	}


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	//app->render->camera.x = app->render->camera.y = 0;
	/*if (app->player->health <= 0)
	{
		app->render->DrawTexture(gameOverImg, 0, 0, NULL, 1.0f);
				
	}*/
	/*if (app->player->win)
	{
		app->render->DrawTexture(WinImage, 0, 0, NULL);
	}*/

	app->render->DrawTexture(idleBackground, 0, 2080, NULL, 1.0f);

	app->render->DrawTexture(gameOverImg, 0, 2080, NULL, 1.0f);

	if (exitButtonG->state == GuiControlState::NORMAL && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButton);
	if (exitButtonG->state == GuiControlState::FOCUSED && exitButtonG->canClick == true) exitButtonG->SetTexture(exitButtonTouch);
	exitButtonG->Draw(app->render);

	return ret;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(gameOverImg);
	app->tex->UnLoad(idleBackground);

	return true;
}