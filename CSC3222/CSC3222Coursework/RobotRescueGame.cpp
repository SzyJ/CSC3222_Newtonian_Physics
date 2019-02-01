#include "RobotRescueGame.h"
#include "SimObject.h"
#include "GameMap.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameSimsPhysics.h"
#include "PlayerRobot.h"
#include "EnemyRobot.h"
#include "CollectableRobot.h"

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"

using namespace NCL;
using namespace CSC3222;

RobotRescueGame::RobotRescueGame()	{
	renderer	= new GameSimsRenderer();
	texManager	= new TextureManager();
	physics		= new GameSimsPhysics();
	SimObject::InitObjects(this, texManager);
	InitialiseGame();
}

RobotRescueGame::~RobotRescueGame()	{
	delete currentMap;
	delete texManager;
	delete renderer;
	delete physics;
}

void RobotRescueGame::Update(float dt) {
	for (auto i : newObjects) {
		gameObjects.emplace_back(i);
	}
	newObjects.clear();

	gameTime += dt;

	renderer->Update(dt);
	physics->Update(dt);
	currentMap->DrawMap(*renderer);

	srand((int)(gameTime * 1000.0f));

	for (auto i = gameObjects.begin(); i != gameObjects.end(); ) {
		if (!(*i)->UpdateObject(dt)) { //object has said its finished with
			delete (*i);
			gameObjects.erase(i);
		}
		else {
			(*i)->DrawObject(*renderer);
			++i;
		}
	}

	renderer->DrawString("Robot Rescue! ", Vector2(380, 700));

	renderer->DrawString("Current Score: " + std::to_string(currentScore), Vector2(10, 10));
	renderer->DrawString("Lives: " + std::to_string(lives), Vector2(850, 10));

	renderer->Render();
}

void RobotRescueGame::InitialiseGame() {
	delete currentMap;
	for (auto o : gameObjects) {
		delete o;
	}
	gameObjects.clear();

	currentMap = new GameMap("GameSimsRobotMap.txt", gameObjects, *texManager);

	renderer->SetScreenProperties(16, currentMap->GetMapWidth(), currentMap->GetMapHeight());

	testRobot = new PlayerRobot();

	AddNewObject(testRobot);

	for (int i = 0; i < 10; ++i) {
		float randomX = 32.0f + (rand() % 416);
		float randomY = 32.0f + (rand() % 256);
		AddEnemyRobot(Vector2(randomX, randomY));
	}

	for (int i = 0; i < 20; ++i) {
		float randomX = 32.0f + (rand() % 416);
		float randomY = 32.0f + (rand() % 256);
		AddCollectableRobot(Vector2(randomX, randomY));
	}

	gameTime		= 0;
	currentScore	= 0;
	lives			= 3;
}

void RobotRescueGame::AddNewObject(SimObject* object) {
	newObjects.emplace_back(object);
	physics->AddRigidBody(object);
	if (object->GetCollider()) {
		physics->AddCollider(object->GetCollider());
	}
}

void RobotRescueGame::AddEnemyRobot(const Vector2& position) {
	EnemyRobot* robot = new EnemyRobot();

	robot->SetPosition(position);

	AddNewObject(robot);
}

void RobotRescueGame::AddCollectableRobot(const Vector2& position) {
	CollectableRobot* robot = new CollectableRobot();

	robot->SetPosition(position);

	AddNewObject(robot);
}