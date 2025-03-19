#include "PlayerAgent.h"

PlayerAgent::PlayerAgent(int keyUp, int keyDown, int keyLeft, int keyRight)
: keyUp(keyUp), keyDown(keyDown), keyLeft(keyLeft), keyRight(keyRight), direction(Vector2(0,0))
{
}

Vector2 PlayerAgent::GetDirection()
{
	return direction;
}

void PlayerAgent::KeyDown(int Key)
{
	#pragma region Handle Direction Input
	if (Key == keyUp)
	{
		direction = Vector2(0, -1);
	}
	if (Key == keyDown)
	{
		direction = Vector2(0, 1);
	}
	if (Key == keyLeft)
	{
		direction = Vector2(-1, 0);
	}
	if (Key == keyRight)
	{
		direction = Vector2(1, 0);
	}
	#pragma	endregion
}
