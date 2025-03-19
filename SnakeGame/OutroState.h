#pragma once
#include "BaseState.h"
class OutroState : public BaseState
{
public:
	OutroState(SnakeGraphics* graphics) : BaseState(graphics) { OutroState::Init(); }

	bool Init() override;
	void Update() override;
	void Render() override;
	void CleanUp() override;

	void KeyDown(int Key) override;
};

