#pragma once
#include <string>

#include "GameObject.h"
#include "PlayerAgent.h"
#include "Tools/SnakeGraphics.h"

enum Levels { LEVEL1, LEVEL2, LEVEL3 };
enum Tags { COLLECTABLE_TAG, OBSTACLE_TAG };

//to-do: make inherited world classes, one for each scene
class World
{
public:
	World(Levels startLevel);

	bool RenderLevel();

	void CheckForObjectCollisions();

	void CreateGameObjects();
	void UpdateGameObjects();
	void RenderGameObjects();
	void DestroyGameObjects();
	void KeyDownGameObjects(int Key); // i don't like this

	void CleanUp();

private:
	std::string levelString;
	std::vector<GameObject*> gameObjects;

	bool LoadLevel(Levels level);

	Vector2 snakeStartPos = Vector2(1,1);
	PlayerAgent* playerBrain;

	//2d array of enums > make all walls "obstacle" positions
};