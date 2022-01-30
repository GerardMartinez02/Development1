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

	animFlag.PushBack({ 0, 0, 30, 30 });
	animFlag.loop = false;
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

	coin1 = app->tex->Load("Assets/textures/items/CoinSprites.png");
	coin2 = app->tex->Load("Assets/textures/items/CoinSprites.png");
	coin3 = app->tex->Load("Assets/textures/items/CoinSprites.png");
	coin4 = app->tex->Load("Assets/textures/items/CoinSprites.png");
	currentCoinAnimation = &anim;

	checkpointFlag = app->tex->Load("Assets/textures/items/blueFlag.png");
	currentFlagAnimation = &animFlag;

	destroyed = false;

	coinPositionOne = app->map->MapToWorld(10, 69);
	coinPositionTwo = app->map->MapToWorld(88, 71);
	coinPositionThree = app->map->MapToWorld(122, 65);
	coinPositionFour = app->map->MapToWorld(156, 68);

	coinBody = app->physics->CreateRectangleSensor(coinPositionOne.x +10, coinPositionOne.y+10, 21, 21, 1);
	coinBody->listener = this;
	coinBody->type = COIN1;
	coinCollected1 = false;

	coinBody = app->physics->CreateRectangleSensor(coinPositionTwo.x + 10, coinPositionTwo.y + 10, 21, 21, 1);
	coinBody->listener = this;
	coinBody->type = COIN2;
	coinCollected2 = false;

	coinBody = app->physics->CreateRectangleSensor(coinPositionThree.x + 10, coinPositionThree.y + 10, 21, 21, 1);
	coinBody->listener = this;
	coinBody->type = COIN3;
	coinCollected3 = false;

	coinBody = app->physics->CreateRectangleSensor(coinPositionFour.x + 10, coinPositionFour.y + 10, 21, 21, 1);
	coinBody->listener = this;
	coinBody->type = COIN4;
	coinCollected4 = false;


	flagPosition = app->map->MapToWorld(96.95, 72.05);
	checkPointBody = app->physics->CreateRectangleSensor(flagPosition.x , flagPosition.y, 21, 21, 1);
	checkPointBody->listener = this;
	checkPointBody->type = CHECKPOINT;

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
	app->render->DrawTexture(coin1, coinPositionOne.x, coinPositionOne.y, &rectCoin);
	app->render->DrawTexture(coin2, coinPositionTwo.x, coinPositionTwo.y, &rectCoin);
	app->render->DrawTexture(coin3, coinPositionThree.x, coinPositionThree.y, &rectCoin);
	app->render->DrawTexture(coin4, coinPositionFour.x, coinPositionFour.y, &rectCoin);

	if (app->player->checkpointReached == true)
	{
		SDL_Rect rectFlag = currentFlagAnimation->GetCurrentFrame();
		app->render->DrawTexture(checkpointFlag, flagPosition.x, flagPosition.y, &rectFlag);
	}
	
	if (app->player->coinTouched1 == true)
	{
		app->tex->UnLoad(coin1);
	}
	if (app->player->coinTouched2 == true)
	{
		app->tex->UnLoad(coin2);
	}
	if (app->player->coinTouched3 == true)
	{
		app->tex->UnLoad(coin3);
	}
	if (app->player->coinTouched4 == true)
	{
		app->tex->UnLoad(coin4);
	}
	/*if (app->player->checkpointReached == true)
	{
		app->render->DrawTexture(checkpointFlag, 97, 72, NULL, 0.75f);
	}*/

	return ret;
}

bool Coins::CleanUp()
{
	LOG("Destroying Coin");
	bool ret = true;
	app->tex->UnLoad(texture);
	app->physics->world->DestroyBody(coinBody->body);
	app->physics->world->DestroyBody(checkPointBody->body);
	//app->tex->UnLoad(coin);
	app->tex->UnLoad(checkpointFlag);
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
