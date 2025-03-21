#pragma once
#include "Tools/SnakeGraphics.h"
#include "BaseState.h"
#include <map>
#include <string>

enum States { MENU_STATE, GAME_STATE, OUTRO_STATE };


class Game
{
public:
	#pragma region Singleton Pattern - getting the instance
	static Game& GetInstance() //singleton pattern - getting the instance
	{
		static Game instance;
		return instance;
	}
	#pragma  endregion

	void Run();

	SnakeGraphics* GetGraphics();
	float GetDeltaTime();

	//these should actually be in a state machine class
	BaseState* GetCurrentState() { return currentState; }
	bool SetState(States newCurrentState);

private:
	#pragma region Singleton Pattern - removing the function of making objects
	Game() {};
	Game(Game const&);			   //overrides default constructor > now you can't make copies of the game class
	void operator = (Game const&); //override assignment operator > now you can't make copies of the game class
	#pragma endregion

	const int FPS = 200;

	SnakeGraphics* m_snakeGraphics = nullptr;
	float m_deltaTime = 0.0f;

	//these should actually be in a state machine class
	std::map <States, BaseState*> availableStatesMap;
	BaseState* currentState;
	States defaultState = MENU_STATE;

	int currentPoints = 0;

	bool Init();
	void Update();
	void Render();
	void CleanUp();

	void KeyDownCallback(int Key);
};
