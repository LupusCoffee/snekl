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
	for (int i = 0; i < levelString.size(); ++i)
	{
		if (levelString[i] == ' ') continue;

		if (levelString[i] == '\n')
		{
			x = 0;
			y++;
			continue;
		}

		if (levelString[i] == 'X' || levelString[i] == 'x') worldMatrix[x][y].tag = Tags::OBSTACLE_TAG;
		else if (levelString[i] == '.') worldMatrix[x][y].tag = Tags::EMPTY_TAG;
		else worldMatrix[x][y].tag = Tags::OBSTACLE_TAG;
		x++;
	}

	return true;
}

bool World::RenderLevel()
{
	if (levelString.size() == 0) return false;

	//plot the level string as tiles
	int x = 0, y = 0;
	for (int i = 0; i < levelString.size(); ++i)
	{
		if (levelString[i] == ' ') continue;

		if (x == WORLD_WIDTH || levelString[i] == '\n')
		{
			x = 0;
			y++;
			continue;
		}

		if (levelString[i] == 'X' || levelString[i] == 'x')
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
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i]->Update();
	}
}

void World::RenderGameObjects()
{
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		gameObjects[i]->Render();
	}

	for (int i = 0; i < WORLD_WIDTH; ++i)
	{
		for (int j = 0; j < WORLD_HEIGHT; ++j)
		{
			if (worldMatrix[i][j].tag == Tags::OBSTACLE_TAG)
				Game::GetInstance().GetGraphics()->PlotTile(i, j, 0, Color(0, 0, 255), WHITE_COLOR, ' ');
		}
	}
}

void World::DestroyGameObjects()
{
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		//remove from list

		gameObjects[i]->Destroy();

		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}

	gameObjects.clear();
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
			if (worldMatrix[i][j].tag == Tags::EMPTY_TAG) c = '.';
			if (worldMatrix[i][j].tag == Tags::OBSTACLE_TAG) c = 'X';

			cout << c << " ";
		}
		cout << "\n";
	}

	DestroyGameObjects();

	delete playerBrain;
	playerBrain = nullptr;

	delete[] worldMatrix;
	worldMatrix = nullptr;
}