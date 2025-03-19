#include "GameState.h"
#include "World.h"
#include <iostream>

#include "Apple.h"
#include "Snake.h"

bool GameState::Init()
{
	scene = World(LEVEL1);
	scene.CreateGameObjects();

	return true;
}

void GameState::Update()
{
	scene.UpdateGameObjects();
}

void GameState::Render()
{
	if (!scene.RenderLevel()) std::cerr << "Level Is Empty \n"; //RENDER LEVEL

	scene.RenderGameObjects();
}

void GameState::CleanUp()
{
	scene.CleanUp();

	BaseState::CleanUp();
}

void GameState::KeyDown(int Key)
{
	scene.KeyDownGameObjects(Key);
}
