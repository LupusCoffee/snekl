#pragma once
#include "BaseAgent.h"
class PlayerAgent : public BaseAgent
{
public:
	PlayerAgent(int keyUp = 0, int keyDown = 0, int keyLeft = 0, int keyRight = 0);

	Vector2 GetDirection() override;
	void KeyDown(int Key);

private:
	int keyUp, keyDown, keyLeft, keyRight;
	Vector2 direction;
};

