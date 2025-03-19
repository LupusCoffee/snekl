#pragma once
#include "stdafx.h"
#include "Tools/RenderHelper.h"
#include "Tools/SnakeGraphics.h"

class BaseState
{
public:
	BaseState(SnakeGraphics* graphics) : m_snakeGraphics(graphics) {}
	virtual ~BaseState();

	virtual bool Init();
	virtual void Update();
	virtual void Render();
	virtual void CleanUp();

	virtual void KeyDown(int Key);

protected:
	SnakeGraphics* m_snakeGraphics = nullptr;
};
