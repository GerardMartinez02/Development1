//#include "EntityManager.h"
//#include "App.h"
//#include "ModulePhysics.h"
//#include "ModulePlayer.h"
//#include "enemyBird.h"
//#include "enemyRedBird.h"
//#include "enemyDragon.h"
//#include "Entity.h"
//#include "Audio.h"
//#include "Map.h"
//#include "Textures.h"
//
//#include "Defs.h"
//#include "Log.h"
//
//EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
//{
//	name.Create("entitymanager");
//}
//
//// Destructor
//EntityManager::~EntityManager()
//{
//	CleanUp();
//}
//
//// Called before render is available
//bool EntityManager::Awake(pugi::xml_node& config)
//{
//	LOG("Loading Entity Manager");
//	bool ret = true;
//	playerFolder.Create(config.child("playerTexture").child_value());
//	birdRedFolder.Create(config.child("bRTexture").child_value());
//	dragonFolder.Create(config.child("dTexture").child_value());
//	birdFolder.Create(config.child("birdTexture").child_value());
//	//L13: TODO 6: Initialize Entities from XML 
//
//	return ret;
//}
//
//bool EntityManager::Start()
//{
//	playerTexxture = app->tex->Load(playerFolder.GetString());
//	birdTexture = app->tex->Load(birdRedFolder.GetString());
//	dragonTexture = app->tex->Load(dragonFolder.GetString());
//	birdTexture = app->tex->Load(birdFolder.GetString());
//
//	return true;
//}
//
//// Called before quitting
//bool EntityManager::CleanUp()
//{
//	bool ret = true;
//	ListItem<Entity*>* item;
//	item = entities.end;
//
//	while (item != NULL && ret == true)
//	{
//		ret = item->data->CleanUp();
//		item = item->prev;
//	}
//
//	entities.clear();
//
//	return ret;
//}
//
//Entity* EntityManager::CreateEntity(EntityType type, iPoint position)
//{
//	Entity* entity = nullptr;
//
//	//L13: TODO 1: Create an Entity and add it to the list of Entities
//	switch (type)
//	{
//	case EntityType::PLAYER:
//	{
//		entity = new Player(position);
//	}break;
//	case EntityType::BIRD:
//	{
//		entity = new bird(position);
//	}break;
//	case EntityType::REDBIRD:
//	{
//		entity = new redBird(position);
//	}break;
//	case EntityType::DRAGON:
//	{
//		entity = new dragon(position);
//	}break;
//	}
//
//	if (entity != nullptr)
//	{
//		entity->pBody->listener = this;
//		entities.add(entity);
//	}
//
//	return entity;
//}
//
//void EntityManager::DestroyEntity(Entity* entity)
//{
//	ListItem<Entity*>* item;
//
//	for (item = entities.start; item != NULL; item = item->next)
//	{
//		if (item->data == entity) entities.del(item);
//	}
//}
//
//void EntityManager::AddEntity(Entity* entity)
//{
//	if (entity != nullptr) entities.add(entity);
//}
//
//bool EntityManager::PreUpdate()
//{
//	for (ListItem<Entity*>* ent = entities.start; ent != nullptr; ent = ent->next)
//	{
//		if (ent->data->pendingToDelete)
//		{
//			DestroyEntity(ent->data);
//			break;
//		}
//	}
//	return true;
//}
//
//bool EntityManager::Update(float dt)
//{
//
//	return true;
//}
//
//bool EntityManager::UpdateAll(float dt, bool doLogic)
//{
//	bool ret = true;
//	ListItem<Entity*>* item;
//	Entity* pEntity = NULL;
//
//	if (doLogic)
//	{
//		for (item = entities.start; item != NULL && ret == true; item = item->next)
//		{
//			pEntity = item->data;
//
//			if (pEntity->active == false) continue;
//			ret = item->data->Update(dt);
//		}
//	}
//
//	return ret;
//}
//
//bool EntityManager::PostUpdate()
//{
//	for (ListItem<Entity*>* ent = entities.start; ent != nullptr; ent = ent->next)
//	{
//		switch (ent->data->type)
//		{
//		case EntityType::PLAYER: app->render->DrawTexture(playerTexxture, ent->data->position.x - 2, ent->data->position.y - 4, &ent->data->currentAnimation->GetCurrentFrame()); break;
//		case EntityType::REDBIRD: app->render->DrawTexture(birdRedTexture, ent->data->position.x - 16, ent->data->position.y - 16, &ent->data->currentAnimation->GetCurrentFrame()); break;
//		case EntityType::DRAGON: app->render->DrawTexture(dragonTexture, ent->data->position.x - 16, ent->data->position.y - 16, &ent->data->currentAnimation->GetCurrentFrame()); break;
//		case EntityType::BIRD: app->render->DrawTexture(birdTexture, ent->data->position.x - 16, ent->data->position.y - 16, &ent->data->currentAnimation->GetCurrentFrame()); break;
//		}
//	}
//	if (app->map->debugColliders == true)
//	{
//		app->map->DrawColliders();
//	}
//
//	return true;
//}
//
//bool EntityManager::LoadState(pugi::xml_node& data)
//{
//	bool ret = true;
//
//	ListItem<Entity*>* item;
//	item = entities.start;
//
//	while (item != NULL && ret == true)
//	{
//		ret = item->data->LoadState(data.child(item->data->name.GetString()));
//		item = item->next;
//	}
//
//	return ret;
//}
//
//bool EntityManager::SaveState(pugi::xml_node& data)
//{
//	bool ret = true;
//
//	ListItem<Entity*>* item;
//	item = entities.start;
//
//	while (item != NULL && ret == true)
//	{
//		//data.append_child(item->data->name.GetString());
//		ret = item->data->SaveState(data.child(item->data->name.GetString()));
//		item = item->next;
//	}
//
//	return ret;
//}
//
//void EntityManager::SetPlayer(Player* player_)
//{
//	player = (Player*)player_;
//}
//
//void EntityManager::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
//{
//	
//
//	if (bodyA->colType == CollisionType::PLAYERCOL && bodyB->colType == CollisionType::CHECKPOINT)
//	{
//		LOG("Checkpoint reached!");
//		player->checkPoint = true;
//	}
//
//	
//
//	//// ENEMY LOGIC 
//	if (bodyA->entityListener->type == PLAYER && bodyB->listener == this && bodyA->listener == this)
//	{
//		if (bodyB->entityListener->type == BIRD || bodyB->entityListener->type == REDBIRD)
//		{
//			if (player->onGround == true)
//			{
//				if (player->GodMode == false && bodyB->listener->active == true) player->playerHit = true;
//			}
//			else
//			{
//				LOG("YOU KILLED THE ENEMY!");
//				if (bodyB->listener->active == true)
//				{
//					player->pBody->body->ApplyLinearImpulse({ -0.6f, -2.4f }, { 0,0 }, true);
//				}
//				bodyB->listener->active = false;
//			}
//		}
//	}
//
//}

