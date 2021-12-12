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
#include "ModuleCollisions.h"
#include "Collider.h"


struct Type;

ModulePlayer::ModulePlayer() : Module()
{
	//idleAnimRight
	idleAnimRight.PushBack({ 0, 1, 31, 35 });
	idleAnimRight.PushBack({ 138, 1, 31, 37 });
	idleAnimRight.loop = true;
	idleAnimRight.speed = 0.008f;

	//idleAnimLeft
	idleAnimLeft.PushBack({ 34, 1, 72, 37 });
	idleAnimLeft.loop = true;
	idleAnimLeft.speed = 0.008f;

	//rightAnim
	leftAnim.PushBack({ 1, 40, 31, 34 });
	leftAnim.PushBack({ 32, 40, 31, 34 });
	leftAnim.PushBack({ 64, 40, 31, 34 });
	leftAnim.PushBack({ 96, 40, 31, 34 });
	leftAnim.PushBack({ 128, 40, 31, 34 });
	leftAnim.PushBack({ 160, 40, 31, 34 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

<<<<<<< Updated upstream
=======
	//runLeftAnim
	runLeftAnim.PushBack({ 156, 160, 31, 37 });
	runLeftAnim.PushBack({ 126, 158, 30, 39 });
	runLeftAnim.PushBack({ 95, 162, 31, 35 });
	runLeftAnim.PushBack({ 66, 162, 29, 35 });
	runLeftAnim.loop = true;
	runLeftAnim.speed = 0.8f;

	//jumpLeftAnimation
	jumpLeftAnim.PushBack({ 126, 122, 30, 35 });
	jumpLeftAnim.PushBack({ 155, 121, 29, 36 });
>>>>>>> Stashed changes

	//leftAnim
	rightAnim.PushBack({ 162, 82, 31, 35 });
	rightAnim.PushBack({ 131, 81, 30, 36 });
	rightAnim.PushBack({ 99, 80, 30, 37 });
	rightAnim.PushBack({ 67, 82, 30, 35 });
	rightAnim.PushBack({ 35, 81, 30, 36 });
	rightAnim.PushBack({ 2, 80, 29, 37 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
<<<<<<< Updated upstream
=======

	//runRightAnim
	runRightAnim.PushBack({ 1, 119, 31, 37 });
	runRightAnim.PushBack({ 31, 117, 30, 39 });
	runRightAnim.PushBack({ 61, 121, 31, 35 });
	runRightAnim.PushBack({ 92, 121, 29, 35 });
	runRightAnim.loop = true;
	runRightAnim.speed = 0.8f;

	//jumpRightAnim
	jumpRightAnim.PushBack({ 31, 163, 30, 35 });
	jumpRightAnim.PushBack({ 3, 162, 29, 36 });
>>>>>>> Stashed changes
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
	currentAnimation = &idleAnimRight;


	//Per fer atacs
	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	destroyed = false;

	position = app->map->MapToWorld(5, 69);

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
	collider = app->collisions->AddCollider({ position.x + 5, position.y + 3, 28, 28 }, Collider::Type::PLAYER, this);
	b->SetUserData(pbody);


	//-----

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;

	//---------------------------------------------------

}

bool ModulePlayer::Update(float dt)
{
	// L10: DONE: Implement gamepad support
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
		if (pbody->body->GetLinearVelocity().x >= -2) pbody->body->ApplyLinearImpulse({ -1.0f,0 }, { 0,0 }, true);
		if (currentAnimation != &rightAnim)
=======
=======
>>>>>>> Stashed changes
		if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT)
		{
			running = true;
		}

		if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_IDLE)
		{
			running = false;
		}
		
		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
>>>>>>> Stashed changes
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

<<<<<<< Updated upstream
<<<<<<< Updated upstream
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.0f,0 }, { 0,0 }, true);
		if (currentAnimation != &leftAnim)
=======
		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT && running == true)
>>>>>>> Stashed changes
=======
		if (app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT && running == true)
>>>>>>> Stashed changes
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	}


=======
=======
>>>>>>> Stashed changes
		
		if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
		{
			if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.0f,0 }, { 0,0 }, true);
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT && running == true)
		{
			if (pbody->body->GetLinearVelocity().x <= +2) pbody->body->ApplyLinearImpulse({ 1.2f,0 }, { 0,0 }, true);
			if (currentAnimation != &runRightAnim)
			{
				runRightAnim.Reset();
				currentAnimation = &runRightAnim;
			}
		}
>>>>>>> Stashed changes

	if (pbody->body->GetLinearVelocity().y == 0)
	{
		jumpsCount = 2;
		jumpState = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN && jumpsCount > 0)
	{
		pbody->body->ApplyLinearImpulse({ 0,-1.4f }, { 0,0 }, true);
		jumpsCount--;
	}

	if (pbody->body->GetLinearVelocity().y > 0 && app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN)
	{
		jumpState = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{
		if (currentAnimation == &rightAnim)
		{
			currentAnimation = &idleAnimLeft;
		}

	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
	{

		//Idle anim left

		if (currentAnimation == &leftAnim)
		{
			currentAnimation = &idleAnimRight;
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

void ModulePlayer::OnCollision(Collider* bodyA, Collider* bodyB)
{
	if (bodyA->type == Collider::Type::PLAYER && bodyB->type == Collider::Type::WINFLAG)
	{
		LOG("WIN!");
		winCondition = true;
	}
	if (bodyA->type == Collider::Type::PLAYER && bodyB->type == Collider::Type::FALL)
	{
		app->scene->Disable();
		//app->player->Disable();
		app->intro->Enable();
	}
}

bool ModulePlayer::loadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();
	pbody->body->SetTransform({ PIXEL_TO_METERS(position.x), PIXEL_TO_METERS(position.y) }, 0.0f);
	return true;
}

bool ModulePlayer::saveState(pugi::xml_node& data) const
{
	data.child("position").attribute("x").set_value(position.x);
	data.child("position").attribute("y").set_value(position.y);
	return true;
}

bool ModulePlayer::CleanUp()
{
	LOG("Cleaning the Player");
	bool ret = true;
	app->tex->UnLoad(texture);
	app->physics->world->DestroyBody(b);
	return true;
}
