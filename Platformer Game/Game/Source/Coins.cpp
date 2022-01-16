#include "Coins.h"
#include "ModulePlayer.h"
#include "Textures.h"
#include "Render.h"
#include "List.h"
#include "App.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "Log.h"
#include "Animation.h"


Coins::Coins() : Module()
{
	anim.PushBack({ 6, 13, 19, 20 });
	anim.PushBack({ 37, 13, 17, 20 });
	anim.PushBack({ 69, 13, 14, 20 });
	anim.PushBack({ 100, 13, 11, 20 });
	anim.PushBack({ 132, 13, 6, 20 });
	anim.PushBack({ 159, 13, 11, 20 });
	anim.PushBack({ 187, 13, 14, 20 });
	anim.PushBack({ 216, 13, 17, 20 });
	anim.loop = true;
	anim.speed = 0.1f;
}

Coins::~Coins()
{
}

bool Coins::Awake(pugi::xml_node& config)
{
	folder.Create(config.child("folder").child_value());
	return true;
}

bool Coins::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	coin = app->tex->Load("Assets/textures/items/CoinSprites.png");
	currentCoinAnimation = &anim;

	destroyed = false;

	coinPosition = app->map->MapToWorld(10, 69);

	coinBody = app->physics->CreateRectangleSensor(coinPosition.x +10, coinPosition.y+10, 21, 21, 1);
	coinBody->listener = this;
	coinBody->type = COIN;
	coinCollected = false;

	return true;
}

bool Coins::PreUpdate()
{
	/*OPTICK_CATEGORY("lvl1 PreUpdate", Optick::Category::Scene);*/
	return true;
}

bool Coins::Update(float dt)
{
	
	/*currentCoinAnimation.Update();*/
		
	return true;
}

bool Coins::PostUpdate()
{
	bool ret = true;

	//Bird
	SDL_Rect rectCoin = currentCoinAnimation->GetCurrentFrame();
	app->render->DrawTexture(coin, coinPosition.x, coinPosition.y, &rectCoin);

	return ret;
}

bool Coins::CleanUp()
{
	LOG("Destroying Coin");
	bool ret = true;
	app->tex->UnLoad(texture);
	app->physics->world->DestroyBody(coinBody->body);
	app->tex->UnLoad(coin);
	return ret;
}

void Coins::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//if (bodyA->type == PLAYER && bodyB->type == COIN)
	//{
	//	LOG("COLLECTED!");
	//	/*app->player->score += 10;*/

	//	app->coins->Disable();
	//}

	//if (c->data->typeCoin == PIZZA)
	//{
	//	/*if (app->player->lives < 5)
	//	{
	//		app->player->lives++;

	//	}*/
	//}

}
