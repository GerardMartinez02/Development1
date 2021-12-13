#ifndef __ENEMYBIRD_H__
#define __ENEMYBIRD_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "List.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePhysics.h"
#include "App.h"

struct SDL_Texture;
struct Collider;

class EnemyBird : public Module,public b2ContactListener
{
public:
	iPoint position;
	// Constructor
	EnemyBird();
	EnemyBird(int x, int y);

	// Destructor
	~EnemyBird();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;


	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);
	void BirdDies();

private:
	PathFinding* pathfinding;
	b2Fixture* enemySensor;

	SDL_Texture* bird;
	SString textureBird;
	SDL_Rect enemyRec;
	SDL_Texture* navigationPath;
	
	Animation idleLeftBird;
	Animation idleRightBird;
	Animation leftBird;
	Animation rightBird;
	Animation* currentBirdAnim = nullptr;
	b2Vec2 BirdVelocity;

	bool birdBoundsRight = false;
	bool birdBoundsLeft = true;

	void enemyBirdMove();
	void enemyBirdPath();
	bool CheckAggro();
	bool aggro;
	int aggroDistance = 8;
	bool setToDestroy = false;
	bool isAlive = true;
	b2Vec2 speed = { 2.0f, -2.0f };
	
public:

	// The current position in the world
	iPoint birdPosition;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	iPoint positionBird;
	iPoint startPosBird;
	
	b2Vec2* velocity;

	PhysBody* birdBody;
	b2Body* bBird;
	b2CircleShape birdCircle;
	const DynArray<iPoint>* currentPath;
	// The speed in which we move the player (pixels per frame)
	
	typeOfCollision* type;
protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	/*iPoint spawnPos;*/
};

#endif;
