#include "ModulePlayer.h"
#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
#include "Log.h"
#include "Scene.h"
#include <stdio.h>
#include <time.h>
#include "ModulePhysics.h"
#include "Map.h"
#include "SceneIntro.h"
#include "Coins.h"
#include "enemyBird.h"
#include "enemyRedBird.h"
#include "enemyDragon.h"
#include "GameOver.h"
#include "ModuleFonts.h"

//#include <SDL_mixer/include/SDL_mixer.h>



ModulePlayer::ModulePlayer() : Module()
{
	name.Create("player");

	//idleAnimRight
	idleAnimRight.PushBack({ 0, 1, 31, 35 });
	idleAnimRight.PushBack({ 138, 1, 31, 37 });
	idleAnimRight.loop = true;
	idleAnimRight.speed = 0.008f;

	//idleAnimLeft
	idleAnimLeft.PushBack({ 34, 1, 72, 37 });
	idleAnimLeft.loop = true;
	idleAnimLeft.speed = 0.008f;

	//lookUp
	lookUpAnim.PushBack({ 2, 1, 30, 37 });

	//lookDown
	lookDownAnim.PushBack({ 142, 0, 30, 37 });


	//leftAnim
	leftAnim.PushBack({ 162, 82, 31, 35 });
	leftAnim.PushBack({ 131, 81, 30, 36 });
	leftAnim.PushBack({ 99, 80, 30, 37 });
	leftAnim.PushBack({ 67, 82, 30, 35 });
	leftAnim.PushBack({ 35, 81, 30, 36 });
	leftAnim.PushBack({ 2, 80, 29, 37 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//runLeftAnim
	runLeftAnim.PushBack({ 162, 82, 31, 35 });
	runLeftAnim.PushBack({ 131, 81, 30, 36 });
	runLeftAnim.PushBack({ 99, 80, 30, 37 });
	runLeftAnim.PushBack({ 67, 82, 30, 35 });
	runLeftAnim.PushBack({ 35, 81, 30, 36 });
	runLeftAnim.PushBack({ 2, 80, 29, 37 });
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.15f;

	//jumpLeftAnimation
	jumpLeftAnim.PushBack({ 126, 122, 30, 35 });
	jumpLeftAnim.PushBack({ 155, 121, 29, 36 });

	//rightAnim
	rightAnim.PushBack({ 1, 41, 31, 35 });
	rightAnim.PushBack({ 33, 40, 30, 36 });
	rightAnim.PushBack({ 65, 39, 30, 37 });
	rightAnim.PushBack({ 97, 41, 30, 35 });
	rightAnim.PushBack({ 129, 40, 30, 36 });
	rightAnim.PushBack({ 163, 39, 29, 37 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	//runRightAnim
	runRightAnim.PushBack({ 1, 41, 31, 35 });
	runRightAnim.PushBack({ 33, 40, 30, 36 });
	runRightAnim.PushBack({ 65, 39, 30, 37 });
	runRightAnim.PushBack({ 97, 41, 30, 35 });
	runRightAnim.PushBack({ 129, 40, 30, 36 });
	runRightAnim.PushBack({ 163, 39, 29, 37 });
	runRightAnim.loop = true;
	runRightAnim.speed = 0.15f;

	//jumpRightAnim
	jumpRightAnim.PushBack({ 31, 163, 30, 35 });
	jumpRightAnim.PushBack({ 3, 162, 29, 36 });
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake(pugi::xml_node&)
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = app->tex->Load("Assets/textures/player/playerSprites.png");
	letterP = app->tex->Load("Assets/textures/items/letterP.png");
	letterI = app->tex->Load("Assets/textures/items/letterI.png");
	letterZ = app->tex->Load("Assets/textures/items/letterZ.png");
	letterA = app->tex->Load("Assets/textures/items/letterA.png");
	currentAnimation = &idleAnimRight;

	playerHitSound = app->audio->LoadFx("Assets/audio/fx/enemyDead.wav");
	coinSound = app->audio->LoadFx("Assets/audio/fx/coinsound.wav");
	enemyHit = app->audio->LoadFx("Assets/audio/fx/enemyHit.wav");
	checkpointSound = app->audio->LoadFx("Assets/audio/fx/checkpoinSound.wav");
	gameOverSound = app->audio->LoadFx("Assets/audio/fx/GameOver.wav");
	fallSound = app->audio->LoadFx("Assets/audio/fx/fallSound.wav");
	playerWinSound = app->audio->LoadFx("Assets/audio/fx/playerWin.wav");


	//Per fer atacs
	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	//destroyed = false;

	if (checkpointReached == false)
	{
		position = app->map->MapToWorld(5, 69);
	}
	if (checkpointReached == true)
	{
		position = app->map->MapToWorld(97, 72);
	}
	if (winCondition == true)
	{
		position = app->map->MapToWorld(5, 69);
	}
	
	//Box2D

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y));
	body.fixedRotation = true;

	b = app->physics->world->CreateBody(&body);

	pCircle.m_radius = PIXEL_TO_METERS(14);

	b2FixtureDef fixture;
	fixture.shape = &pCircle;
	fixture.density = 1.5f;
	fixture.friction = 100.0f;

	b->CreateFixture(&fixture);

	pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = pCircle.m_radius;
	pbody->listener = this;
	pbody->type = PLAYER;
	b->SetUserData(pbody);

	delay = 0;

	if (playerLifeCount == true)
	{
		playerLifeCount = false;
	}

	char lookupTable[] = { "0123456789" };
	timeFont = app->fonts->Load("Assets/textures/ui/numbers.png", lookupTable, 1);
	scoreFont = app->fonts->Load("Assets/textures/ui/numbers2.png", lookupTable, 1);
	//timeFont = App->fonts->Load("Assets/Art/UI/numbers2.png", lookupTable, 1);
	//-----

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;

	//---------------------------------------------------

}

bool ModulePlayer::Update(float dt)
{
	delay++;

	if (pauseMenu == true)
	{
		iPoint NewPosition = position;
		pbody->GetPosition(NewPosition.x, NewPosition.y);
		return true;
	}
	if (pauseMenu == false)
	{


		// L10: DONE: Implement gamepad support
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_IDLE)
		{
			if (pbody->body->GetLinearVelocity().x >= -2) pbody->body->ApplyLinearImpulse({ -1.0f,0 }, { 0,0 }, true);
			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT)
		{
			if (pbody->body->GetLinearVelocity().x >= -2) pbody->body->ApplyLinearImpulse({ -1.2f,0 }, { 0,0 }, true);
			if (currentAnimation != &runLeftAnim)
			{
				runLeftAnim.Reset();
				currentAnimation = &runLeftAnim;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_IDLE)
		{
			if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.0f,0 }, { 0,0 }, true);
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT)
		{
			if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.2f,0 }, { 0,0 }, true);
			if (currentAnimation != &runRightAnim)
			{
				runRightAnim.Reset();
				currentAnimation = &runRightAnim;
			}
		}

		//JUMP

		if (pbody->body->GetLinearVelocity().y == 0)
		{
			jumpsCount = 2;
			jumpState = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN && jumpsCount > 0)
		{
			pbody->body->ApplyLinearImpulse({ 0,-1.4f }, { 0,0 }, true);
			if (app->scene->godMode == false)
			{
				jumpsCount--;
			}
		}

		if (pbody->body->GetLinearVelocity().y > 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN)
		{
			jumpState = true;
		}

		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_IDLE)
		{
			if (currentAnimation == &leftAnim)
			{
				currentAnimation = &idleAnimLeft;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_IDLE
			&& app->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_IDLE)
		{
			//Idle anim left

			if (currentAnimation == &rightAnim)
			{
				currentAnimation = &idleAnimRight;
			}

		}

		if (checkpoint == true)
		{
			checkpointReached = true;
		}

		if ((delay % 60) == 0)
		{
			/*
			if (timeCounter <= 0)
			{
				timeCounter == 0;
			}
			*/
			timeCounter--;
		}

		if (playerHit == true)
		{
			app->audio->PlayFx(playerHitSound);
			playerHealth = playerHealth;
			if ((delay % 60) == 0)
			{
				hitDelay++;
				if ((hitDelay % 1) == 0)
				{
					playerHit = false;
				}
			}
		}


		if (playerHealth != 0)
		{
			currentAnimation->Update();
		}

		pbody->GetPosition(position.x, position.y);
	}
		return true;
}

bool ModulePlayer::PostUpdate()
{
	/*if (!destroyed)
	{

	}*/

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x -16, position.y -16, &rect);

	// Draw UI (score) --------------------------------------
	//sprintf_s(scoreText, 10, "%5d", score);
	
	
	sprintf_s(timeText, 10, "%3d", timeCounter);
	sprintf_s(scoreText, 10, "%4d", score);
	
	

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//app->fonts->BlitText(58, 248, scoreFont, scoreText);

	//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

	SDL_Rect healthIndicator;
	healthIndicator = { 5, 10, playerHealth, 10 };

	if (playerHealth >= 75)
	{
		playerHealth = 75;
		app->render->DrawQuad(healthIndicator, 0, 255, 0, 255, 0.0f, true);
	}
	else if (playerHealth > 40)
	{
		app->render->DrawQuad(healthIndicator, 120, 255, 0, 255, 0.0f, true);
	}
	else if (playerHealth > 0 && playerHealth <= 30)
	{
		app->render->DrawQuad(healthIndicator, 255, 255, 0, 255, 0.0f, true);
	}
	else
	{
		if ((app->FPS / 5) % 2 == 0)
		{
			app->render->DrawRectangle(healthIndicator, 255, 0, 0, 255, 0.0f, true);
		}
		else
		{
			app->render->DrawRectangle(healthIndicator, 255, 150, 0, 255, 0.0f, true);
		}

	}

	if (timeCounter == 0 && app->scene->godMode == false)
	{
		playerHealth = 0;
	}

	// Timer
	if (playerHealth != 0)
	{
		app->fonts->BlitText(520, 60, timeFont, timeText);
		app->fonts->BlitText(30, 50, scoreFont, scoreText);
	}
	
	if (playerHealth != 0)
	{
		if (coinTouched1 == true)
		{
			app->render->DrawTexture(letterP, 500, 11.5, NULL, 0, true);
		}
		if (coinTouched2 == true)
		{
			app->render->DrawTexture(letterI, 520, 10, NULL, 0, true);
		}
		if (coinTouched3 == true)
		{
			app->render->DrawTexture(letterZ, 540, 10, NULL, 0, true);
		}
		if (coinTouched4 == true)
		{
			app->render->DrawTexture(letterA, 560, 10, NULL, 0, true);
		}
	}

	if (playerHealth == 0)
	{
		//Mix_PauseMusic();
		app->audio->PlayFx(gameOverSound);
		app->scene->Disable();
		app->coins->Disable();
		app->enemyBird->Disable();
		app->enemyDragon->Disable();
		//app->player->Disable();
		app->gameOver->Enable();
		playerHealth = 75;
		timeCounter = 120;
		checkpoint = false;
		checkpointReached = false;
		coinTouched1 = false;
		coinTouched2 = false;
		coinTouched3 = false;
		coinTouched4 = false;
		score = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && app->player->destroyed == false && app->player->winCondition == false)
	{
		/*app->audio->PlayFx(paused);*/
		pauseMenu = !pauseMenu;
	}

	return true;
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA->type == PLAYER && bodyB->type == WINFLAG)
	{

		LOG("WIN!");
		app->audio->PlayFx(playerWinSound);
		winCondition = true;
		app->scene->Disable();
		//app->player->Disable();
		app->intro->Enable();
		timeCounter = 120;
		playerHealth = 75;
		checkpoint = false;
		checkpointReached = false;
		coinTouched1 = false;
		coinTouched2 = false;
		coinTouched3 = false;
		coinTouched4 = false;
		score = 0;
	}
	if (bodyA->type == PLAYER && bodyB->type == CHECKPOINT)
	{
		if (checkpoint == false)
		{
			app->audio->PlayFx(checkpointSound);
		}
		winCondition = false;
		checkpoint = true;
	}
	if (bodyA->type == PLAYER && bodyB->type == FALL && app->scene->godMode == false)
	{
		//app->scene->Disable();
		//app->coins->Disable();
		//app->enemyBird->Disable();
		//app->enemyDragon->Disable();
		////app->player->Disable();
		//app->gameOver->Enable();
		
		if (playerHealth == 75 && playerLifeCount == false)
		{
			playerHealth = 60;
			app->audio->PlayFx(fallSound);
			playerLifeCount = true;
		}
		if (playerHealth == 60 && playerLifeCount == false)
		{
			playerHealth = 45;
			app->audio->PlayFx(fallSound);
			playerLifeCount = true;
		}
		if (playerHealth == 45 && playerLifeCount == false)
		{
			playerHealth = 30;
			app->audio->PlayFx(fallSound);
			playerLifeCount = true;
		}
		if (playerHealth == 30 && playerLifeCount == false)
		{
			playerHealth = 15;
			app->audio->PlayFx(fallSound);
			playerLifeCount = true;
		}
		if (playerHealth == 15 && playerLifeCount == false)
		{
			playerHealth = 0;
			app->audio->PlayFx(fallSound);
			playerLifeCount = true;
		}
		

		if (checkpointReached == false)
		{
			spawnPosition = 1;
		}

		if (checkpointReached == true)
		{
			spawnPosition = 2;
		}
	}
	if (bodyA->type == PLAYER && bodyB->type == BIRD && app->scene->godMode == false)
	{
		if (jumpsCount == 2)
		{
			//app->scene->Disable();
			//app->coins->Disable();
			//app->enemyBird->Disable();
			//app->enemyDragon->Disable();
			////app->player->Disable();
			//app->gameOver->Enable();

			
			if (playerHealth == 75 )
			{
				playerHealth = 60;
				playerHit = true;
			}
			if (playerHealth == 60 && playerHit == false)
			{
				playerHealth = 45;
				playerHit = true;
	
			}
			if (playerHealth == 45 && playerHit == false)
			{
				playerHealth = 30;
				playerHit = true;
				
			}
			if (playerHealth == 30 && playerHit == false)
			{
				playerHealth = 15;
				playerHit = true;
				
			}
			if (playerHealth == 15 && playerHit == false)
			{
				playerHealth = 0;
				playerHit = true;
			}

		}

		else if (jumpsCount == 1 || jumpsCount == 0)
		{
			app->audio->PlayFx(enemyHit);
			app->enemyBird->Disable();
			score = score + 25;
		}
	}

	if (bodyA->type == PLAYER && bodyB->type == REDBIRD && app->scene->godMode == false)
	{
		if (jumpsCount == 2)
		{
			//app->scene->Disable();
			//app->coins->Disable();
			//app->enemyBird->Disable();
			//app->enemyDragon->Disable();
			////app->player->Disable();
			//app->gameOver->Enable();


			if (playerHealth == 75)
			{
				playerHealth = 60;
				playerHit = true;
			}
			if (playerHealth == 60 && playerHit == false)
			{
				playerHealth = 45;
				playerHit = true;

			}
			if (playerHealth == 45 && playerHit == false)
			{
				playerHealth = 30;
				playerHit = true;

			}
			if (playerHealth == 30 && playerHit == false)
			{
				playerHealth = 15;
				playerHit = true;

			}
			if (playerHealth == 15 && playerHit == false)
			{
				playerHealth = 0;
				playerHit = true;
			}

		}

		else if (jumpsCount == 1 || jumpsCount == 0)
		{
			app->audio->PlayFx(enemyHit);
			app->enemyRedBird->Disable();
			score = score + 25;
		}
	}
	if (bodyA->type == PLAYER && bodyB->type == DRAGON && app->scene->godMode == false)
	{
		if (jumpsCount == 2)
		{
			//app->scene->Disable();
			//app->coins->Disable();
			//app->enemyBird->Disable();
			//app->enemyDragon->Disable();
			////app->player->Disable();
			//app->gameOver->Enable();
			if (playerHealth == 75)
			{
				playerHealth = 60;
				playerHit = true;
			}
			if (playerHealth == 60 && playerHit == false)
			{
				playerHealth = 45;
				playerHit = true;

			}
			if (playerHealth == 45 && playerHit == false)
			{
				playerHealth = 30;
				playerHit = true;

			}
			if (playerHealth == 30 && playerHit == false)
			{
				playerHealth = 15;
				playerHit = true;

			}
			if (playerHealth == 15 && playerHit == false)
			{
				playerHealth = 0;
				playerHit = true;
			}
		}

		else if (jumpsCount == 1 || jumpsCount == 0)
		{
			app->audio->PlayFx(enemyHit);
			app->enemyDragon->Disable();
			score = score + 25;
		}
	}
	if (bodyA->type == PLAYER && bodyB->type == COIN1)
	{
		//app->scene->Disable();
		//app->player->Disable();
		//app->intro->Enable();
		/*app->coins->Disable();*/

		if (coinTouched1 == false)
		{
			app->audio->PlayFx(coinSound);
			score = score + 100;
		}

		coinTouched1 = true;

		
	}
	if (bodyA->type == PLAYER && bodyB->type == COIN2)
	{
		//app->scene->Disable();
		//app->player->Disable();
		//app->intro->Enable();
		/*app->coins->Disable();*/

		if (coinTouched2 == false)
		{
			app->audio->PlayFx(coinSound);
			score = score + 100;
		}

		coinTouched2 = true;
		
	}
	if (bodyA->type == PLAYER && bodyB->type == COIN3)
	{
		//app->scene->Disable();
		//app->player->Disable();
		//app->intro->Enable();
		/*app->coins->Disable();*/

		if (coinTouched3 == false)
		{
			app->audio->PlayFx(coinSound);
			score = score + 100;
		}

		coinTouched3 = true;
	
	}
	if (bodyA->type == PLAYER && bodyB->type == COIN4)
	{
		//app->scene->Disable();
		//app->player->Disable();
		//app->intro->Enable();
		/*app->coins->Disable();*/

		if (coinTouched4 == false)
		{
			app->audio->PlayFx(coinSound);
			score = score + 100;
		}

		coinTouched4 = true;
	
	}
	if (bodyA->type == PLAYER && bodyB->type == PIZZA)
	{
		//app->scene->Disable();
		//app->player->Disable();
		//app->intro->Enable();
		/*app->coins->Disable();*/

		if (pizzaTouched == false)
		{
			app->audio->PlayFx(coinSound);
			playerHealth = playerHealth + 30;
		}

		pizzaTouched = true;
	}
}


bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	score = data.child("atributes").attribute("score").as_int();
	playerHealth = data.child("atributes").attribute("playerHealth").as_int();


	pbody->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0.0f);
	return true;
}

bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node playerPosition = data.append_child("position");
	pugi::xml_node atributes = data.append_child("atributes");

	playerPosition.append_attribute("x") = position.x;
	playerPosition.append_attribute("y") = position.y;

	atributes.append_attribute("score") = score;
	atributes.append_attribute("playerHealth") = playerHealth;

	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Cleaning the Player");
	bool ret = true;
	app->tex->UnLoad(texture);
	app->tex->UnLoad(letterP);
	app->tex->UnLoad(letterI);
	app->tex->UnLoad(letterZ);
	app->tex->UnLoad(letterA);
	app->fonts->UnLoad(timeFont);
	app->fonts->UnLoad(scoreFont);
	app->physics->world->DestroyBody(b);
	return true;
}
