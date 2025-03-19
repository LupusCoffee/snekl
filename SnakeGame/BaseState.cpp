#include "BaseState.h"

#include <iostream>

BaseState::~BaseState()
{
	std::cout << "Base State Killed \n";
}

bool BaseState::Init()
{
	return true;
}

void BaseState::Update()
{
}

void BaseState::Render()
{
}

void BaseState::CleanUp()
{
	m_snakeGraphics->ClearRender();
}

void BaseState::KeyDown(int Key)
{
}
