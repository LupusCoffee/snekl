#include "World.h"
#include "stdafx.h"
#include <fstream>
#include <string>

#include "Apple.h"
#include "Game.h"
#include "Snake.h"

World::World(Levels startLevel)
{
	LoadLevel(startLevel);
	playerBrain = new PlayerAgent(38, 40, 37, 39);
}

#pragma region Handle Level
bool World::LoadLevel(Levels level)
{
	std::string fileToLoad;

	switch (level)
	{
	case LEVEL1: fileToLoad = "Levels/Level1.txt"; break;
	case LEVEL2: fileToLoad = "Levels/Level2.txt"; break;
	case LEVEL3: fileToLoad = "Levels/Level3.txt";	break;
	}

	//add contents of readFile to levelString
	std::ifstream readFile(fileToLoad);
	if (!readFile) return false;

	levelString.assign((std::istreambuf_iterator<char>(readFile)), (std::istreambuf_iterator<char>()));
	return true;
}

bool World::RenderLevel()
{
	if (levelString.size() == 0) return false;

	//plot the level string as tiles
	int x = 0, y = 0;
	for (auto element : levelString)
	{
		if (element == ' ') continue;

		if (x == WORLD_WIDTH || element == '\n')
		{
			x = 0;
			y++;
			continue;
		}

		if (element == '+') snakeStartPos = Vector2(x,y); //why is this being detected so much???

		if (element == 'X' || element == 'x') Game::GetInstance().GetGraphics()->PlotTile(x, y, 0, OBSTACLE_COLOR, OBSTACLE_COLOR, ' ');
		x++;
	}

	return true;
}
#pragma endregion

#pragma region Handle GameObjects
void World::CreateGameObjects()
{
	gameObjects.push_back(new Apple(6, 6, {COLLECTABLE}, TURQUOISE_COLOR));
	gameObjects.push_back(new Snake(playerBrain, 0.3f, 2, 10, 10, {SNAKE}, DARKER_RED_COLOR));
}

void World::UpdateGameObjects()
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->IsDestroy()) continue;
		gameObject->Update();
	}
}

void World::RenderGameObjects()
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->IsDestroy()) continue;
		gameObject->Render();
	}
}

void World::DestroyGameObjects()
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->IsDestroy()) continue;
		//remove from list
		gameObject->Destroy();
	}
}

void World::KeyDownGameObjects(int Key)
{
	playerBrain->KeyDown(Key);
}

void World::CheckForObjectCollisions()
{
	for (auto obj : gameObjects)
	{
		for (auto colObj : gameObjects)
		{
			if (obj == colObj) continue;

			//if obj and colObj has same position >>> obj.OnCollision(colObj);
			if (obj->GetPosition().x == colObj->GetPosition().x && obj->GetPosition().y == colObj->GetPosition().y) //need to make an overloaded operator for it
				obj->OnCollision(colObj);
		}
	}
}
#pragma endregion

void World::CleanUp()
{
	DestroyGameObjects();

	delete playerBrain;
}