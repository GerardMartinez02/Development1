#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "Timer.h"
#include "AuxTimer.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class PathFinding;
class SceneIntro;
class Map;

class ModuleFadeToBlack;
class ModulePhysics;
class ModulePlayer;
class SceneIntro;
class GameOver;
class EnemyBird;
class EnemyDragon;
class Timer;
class AuxTimer;

enum sceneEnum
{
	TITLE,
	SCENE
};

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadFile();
	bool SaveFile() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	SceneIntro* intro;
	PathFinding* pathfinding;
	GameOver* gameOver;
	Map* map;
	
	ModuleFadeToBlack* fadeToBlack;
	ModulePhysics* physics;
	ModulePlayer* player;
	SceneIntro* sceneIntro;
	EnemyBird* enemyBird;
	EnemyDragon* enemyDragon;
	
	bool fpsCap = false;
	float dt = 0.0f;
	uint32 FPS = 0;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	pugi::xml_document configFile;
	pugi::xml_document gameStateFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	AuxTimer* frameDuration;
	AuxTimer* ptimer;

	Timer startupTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 lastSecFrameCount = 0;
	uint32 maxFR = 0;

	float average = 0.0f;
};

extern App* app;

#endif	// __APP_H__