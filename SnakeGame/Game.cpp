#include "stdafx.h"
#include "Game.h"
#include "MenuState.h"
#include "Tools/SnakeGraphics.h"
#include "Tools/SnakeInput.h"
#include "Tools/RenderHelper.h"
#include <iostream>
#include <chrono>
#include <thread>

#include "GameState.h"
#include "OutroState.h"


void Game::Run()
{
	if (!Init())
	{
		std::cerr << "Init failed! \n";

		return;
	}

	std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();

	while (m_snakeGraphics->UpdateWindowMessages()) //MAIN LOOP
	{
		Update();

		Render();

		//timer and fps stuff
		std::chrono::duration<double, std::milli> work_time = std::chrono::system_clock::now() - timer;
		long timeLeft = (1000 / FPS) - (long)work_time.count();
		if (timeLeft > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(timeLeft));
		}
		std::chrono::duration<double, std::milli> deltaTime = std::chrono::system_clock::now() - timer;
		m_deltaTime = (float)deltaTime.count() / 1000.0f;
		//std::cout << "Delta time: " << m_deltaTime << std::endl;
		timer = std::chrono::system_clock::now();
	}

	CleanUp();
}

SnakeGraphics* Game::GetGraphics()
{
	return m_snakeGraphics;
}

float Game::GetDeltaTime()
{
	return m_deltaTime;
}

bool Game::Init()
{
	// Init snake graphics
	m_snakeGraphics = new SnakeGraphics(1000, 1000, WORLD_WIDTH, WORLD_HEIGHT);

	if (!m_snakeGraphics->Init())
	{
		std::cerr << "Failed to initilize snake graphics!" << std::endl;

		return false;
	}

	//States
	availableStatesMap.insert
	({
		{MENU_STATE, new MenuState(m_snakeGraphics)},
		{GAME_STATE, new GameState(m_snakeGraphics)},
		{OUTRO_STATE, new OutroState(m_snakeGraphics)},
	});
	SetState(defaultState);


	// Init snake input
	if (!SnakeInput::Init(m_snakeGraphics))
	{
		std::cerr << "Failed to initialize snake input! \n";

		return false;
	}

	SnakeInput::AddKeyDownCallback(std::bind(&Game::KeyDownCallback, this, std::placeholders::_1));

	return true;
}

void Game::Update()
{
	currentState->Update();
}

void Game::Render()
{
	currentState->Render();

	m_snakeGraphics->Render();
}

void Game::CleanUp()
{
	SnakeInput::CleanUp();

	currentState->CleanUp();

	delete m_snakeGraphics;
}

void Game::KeyDownCallback(int Key)
{
	std::cout << "Keydown: " << Key << "\n";

	//escape > close down window
	if (Key == 27)
	{
		CleanUp();
		exit(0); //kinda bad?
	}

	currentState->KeyDown(Key);
}

bool Game::SetState(States newCurrentState)
{
	if (currentState != nullptr) currentState->CleanUp();

	currentState = availableStatesMap.at(newCurrentState);

	currentState->Init();

	return true;
}
