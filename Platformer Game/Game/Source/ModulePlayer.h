#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Box2D/Box2D/Box2D.h"
#include "ModuleFadeToBlack.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called before all Updates
	bool PostUpdate() override;

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	// Called before quitting
	bool CleanUp();

	// Collision callback, called when the player intersects with another collider


public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	PhysBody* pbody;
	b2Body* b;

	b2CircleShape pCircle;
	b2PolygonShape pBox;


	int speed = 1;
	bool jumpState = false;
	int jumpsCount;

	bool checkpoint = false;
	bool checkpointReached = false;

	bool coinTouched1 = false;
	bool coinTouched2 = false;
	bool coinTouched3 = false;
	bool coinTouched4 = false;

	bool winCondition = false;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture;
	SDL_Texture* letterP = nullptr;
	SDL_Texture* letterI = nullptr;
	SDL_Texture* letterZ = nullptr;
	SDL_Texture* letterA = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnimRight;
	Animation idleAnimLeft;
	Animation lookUpAnim;
	Animation lookDownAnim;
	Animation leftAnim;
	Animation runLeftAnim;
	Animation jumpLeftAnim;
	Animation rightAnim;
	Animation runRightAnim;
	Animation jumpRightAnim;

	int currentScene;

	// The player's collider


	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 0000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int horizontalMargin = 45;

	//Margin of movement

	bool debugMode;
	bool horizonalCamera;
	bool verticalCamera;

	int playerHealth = 75;
	bool playerLifeCount = false;

	int hitDelay = 0;
	bool playerHit = false;

	int spawnPosition = 0;

	//Timer

	int delay;
	int timeFont = -1;
	char timeText[10] = { "\0" };
	uint timeCounter = 120;

};

#endif //!__MODULE_PLAYER_H__