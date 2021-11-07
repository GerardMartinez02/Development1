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




ModulePlayer::ModulePlayer() : Module()
{
	//idleAnim
	idleAnim.PushBack({ 0, 1, 31, 35 });
	idleAnim.PushBack({ 138, 1, 31, 37 });
	idleAnim.loop = true;
	idleAnim.speed = 0.008f;

	//rightAnim
	leftAnim.PushBack({ 1, 40, 31, 34 });
	leftAnim.PushBack({ 32, 40, 31, 34 });
	leftAnim.PushBack({ 64, 40, 31, 34 });
	leftAnim.PushBack({ 96, 40, 31, 34 });
	leftAnim.PushBack({ 128, 40, 31, 34 });
	leftAnim.PushBack({ 160, 40, 31, 34 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;


	//leftAnim
	rightAnim.PushBack({ 1, 80, 31, 34 });
	rightAnim.PushBack({ 32, 80, 31, 34 });
	rightAnim.PushBack({ 64, 80, 31, 34 });
	rightAnim.PushBack({ 96, 80, 31, 34 });
	rightAnim.PushBack({ 128, 80, 31, 34 });
	rightAnim.PushBack({ 160, 80, 31, 34 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
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

	texture = app->tex->Load("Assets/textures/playerSprites.png");
	currentAnimation = &idleAnim;

	//Per fer atacs
	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	destroyed = false;

	//position = app->map->MapToWorld(61, 39);

	//Box2D

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y));
	body.fixedRotation = true;

	b = app->physics->world->CreateBody(&body);

	pCircle.m_radius = PIXEL_TO_METERS(14);

	b2FixtureDef fixture;
	fixture.shape = &pCircle;
	fixture.density = 2.0f;
	fixture.friction = 100.0f;

	b->CreateFixture(&fixture);

	pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = pCircle.m_radius;
	pbody->listener = this;

	//-----

	jumpCounter = 0;
	
	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;
}

bool ModulePlayer::Update(float dt)
{
	// L10: DONE: Implement gamepad support
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (pbody->body->GetLinearVelocity().x >= -2) pbody->body->ApplyLinearImpulse({ -1.0f,0 }, { 0,0 }, true);
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.0f,0 }, { 0,0 }, true);
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	
	
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		pbody->body->ApplyLinearImpulse({ 0,-2 }, { 0,0 }, true);
		jumpCounter++;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{
		if (currentAnimation == &rightAnim)
		{
			currentAnimation = &idleAnim;
		}

		//Idle anim left
		
		if (currentAnimation == &leftAnim)
		{
			currentAnimation = &idleAnim;
		}
		
	}

	currentAnimation->Update();

	pbody->GetPosition(position.x, position.y);

	return true;
}

bool ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{

	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &rect);

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//app->fonts->BlitText(58, 248, scoreFont, scoreText);

	//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

	return true;
}

bool ModulePlayer::CleanUp() // Implementar???
{
	return true;
}
