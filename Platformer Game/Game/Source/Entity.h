#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Input.h"
#include "Render.h"
#include "Animation.h"
#include "ModulePhysics.h"

struct Collider;

enum EntityType
{

};

struct SDL_Texture;
class PhysBody;
class EntityManager;

class Entity
{
public:

	Entity(EntityType type, iPoint position_) : type(type), position(position_) {}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB)
	{

	};

	iPoint GetPos()
	{
		return position;
	}

public:

	SString name;
	EntityType type;
	bool active = true;
	//uint32 id;            // Entity identifier?
	bool pendingToDelete;
	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	PhysBody* pBody;
	iPoint position;
	iPoint startPos;
	Animation* currentAnimation;
	b2Vec2 velocity;
	bool renderable = false;
	//SDL_Texture* texture;
	int height, width;
};

#endif // __ENTITY_H__