#include "stdafx.h"
#include "World.h"
#include <fstream>
#include <iostream>
#include <string>

#include "Apple.h"
#include "Game.h"
#include "Snake.h"

using std::cout;

World::World(Levels startLevel)
{
	worldMatrix = new WorldTile*[WORLD_WIDTH];
	for (int i = 0; i < WORLD_WIDTH; i++) worldMatrix[i] = new WorldTile[WORLD_HEIGHT];


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
	case LEVEL3: fileToLoad = "Levels/Level3.txt"; break;
	}

	//add contents of readFile to levelString
	std::ifstream readFile(fileToLoad);
	if (!readFile) return false;

	levelString.assign((std::istreambuf_iterator<char>(readFile)), (std::istreambuf_iterator<char>()));

	if (levelString.size() == 0) return false;

	//set obstacle and empty tags
	int x = 0, y = 0;
	int bitchAss = 0;
	for (auto element : levelString)
	{
		if (element == ' ') continue;

		if (element == '\n')
		{
			x = 0;
			y++;
			continue;
		}

		if (element == 'X' || element == 'x') worldMatrix[x][y].tag = OBSTACLE_TAG;
		else if (element == '.') worldMatrix[x][y].tag = EMPTY_TAG;
		else worldMatrix[x][y].tag = OBSTACLE_TAG;
		x++;
	}

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

		if (element == 'X' || element == 'x')
			Game::GetInstance().GetGraphics()->PlotTile(x, y, 0, OBSTACLE_COLOR, OBSTACLE_COLOR, ' ');
		x++;
	}

	return true;
}
#pragma endregion

#pragma region Handle GameObjects
void World::CreateGameObjects()
{
	gameObjects.push_back(new Snake(worldMatrix, playerBrain, 0.1f, 2, 32, 30, { SNAKE }, DARKER_RED_COLOR));
	gameObjects.push_back(new Apple(worldMatrix, 28, 30, {COLLECTABLE}, TURQUOISE_COLOR));
}

void World::UpdateGameObjects()
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsDestroy()) continue;
		gameObject->Update();
	}
}

void World::RenderGameObjects()
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->IsDestroy()) continue;
		gameObject->Render();
	}

	for (int i = 0; i < WORLD_WIDTH; ++i)
	{
		for (int j = 0; j < WORLD_HEIGHT; ++j)
		{
			if (worldMatrix[i][j].tag == OBSTACLE_TAG)
				Game::GetInstance().GetGraphics()->PlotTile(i, j, 0, Color(0, 0, 255), WHITE_COLOR, ' ');
		}
	}
}

void World::DestroyGameObjects()
{
	for (auto& gameObject : gameObjects)
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
#pragma endregion

void World::CleanUp()
{
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			char c = '0';
			if (worldMatrix[i][j].tag == 0) c = '.';
			if (worldMatrix[i][j].tag == 2) c = 'X';

			cout << c << " ";
		}
		cout << "\n";
	}

	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		cout << i;
		delete[] worldMatrix[i];
	}
	delete[] worldMatrix;

	DestroyGameObjects();

	delete playerBrain;
}