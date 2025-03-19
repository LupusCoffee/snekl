#pragma once
#include "GameObject.h"

class BaseAgent
{
public:
	virtual Vector2 GetDirection() = 0;
	virtual void KeyDown(int Key);
};

