#pragma once
#include "BaseState.h"
#include "World.h"

class GameState : public BaseState
{
public:
	GameState(SnakeGraphics* graphics) : BaseState(graphics), scene(World(LEVEL1)) {}

	bool Init() override;
	void Update() override;
	void Render() override;
	void CleanUp() override;

	void KeyDown(int Key) override;

private:
	World scene;
};

