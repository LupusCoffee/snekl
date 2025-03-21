#include "MenuState.h"
#include <iostream>

#include "Game.h"


void MenuItem::Render()
{
	if (isHovering)
	{
		snakeGraphics->PlotText(24, WORLD_HEIGHT / 4 + 5 + menuHeight, 0, hoverBackgroundColor, displayText, hoverTextColor, SnakeGraphics::Left);
	}
	else
	{
		snakeGraphics->PlotText(24, WORLD_HEIGHT / 4 + 5 + menuHeight, 0, idleBackgroundColor, displayText, idleTextColor, SnakeGraphics::Left);
	}
}
void MenuItem::SetHover(bool _bool)
{
	isHovering = _bool;
}
void MenuItem::Click()
{
	if (displayText == L"play")
	{
		Game::GetInstance().SetState(GAME_STATE);
	}
}


bool MenuState::Init()
{
	play = new MenuItem(m_snakeGraphics, L"play", PURE_BLACK_COLOR, WHITE_COLOR, LESS_RED_COLOR, PURE_BLACK_COLOR, 1);
	about = new MenuItem(m_snakeGraphics, L"about", PURE_BLACK_COLOR, WHITE_COLOR, LESS_RED_COLOR, PURE_BLACK_COLOR, 2);
	quit = new MenuItem(m_snakeGraphics, L"quit", PURE_BLACK_COLOR, WHITE_COLOR, LESS_RED_COLOR, PURE_BLACK_COLOR, 3);

	return true;
}

void MenuState::Update()
{
	
}

void MenuState::Render()
{
	//Title - only in menu
	m_snakeGraphics->PlotText(24, WORLD_HEIGHT / 4 + 5, 0, RED_COLOR, L"SUNEIKU DA!!", PURE_BLACK_COLOR, SnakeGraphics::Left);

	//only in menu
	play->Render();
	about->Render();
	quit->Render();
}

void MenuState::CleanUp()
{
	delete play;
	delete about;
	delete quit;

	BaseState::CleanUp();
}

void MenuState::KeyDown(int Key)
{
	//up
	if (Key == 87 || Key == 38)
	{
		m_menuNav--;
		if (m_menuNav < m_minNav) m_menuNav = m_maxNav;
	}
	//down
	else if (Key == 83 || Key == 40)
	{
		m_menuNav++;
		if (m_menuNav > m_maxNav) m_menuNav = m_minNav;
	}
	if (m_menuNav == 0) //play
	{
		play->SetHover(true);
		about->SetHover(false);
		quit->SetHover(false);
	}
	else if (m_menuNav == 1) //about
	{
		play->SetHover(false);
		about->SetHover(true);
		quit->SetHover(false);
	}
	else //quit
	{
		play->SetHover(false);
		about->SetHover(false);
		quit->SetHover(true);
	}

	//click
	if (Key == 32 || Key == 13)
	{
		if (m_menuNav == 0) play->Click();
		else if (m_menuNav == 1) about->Click();
		else quit->Click();
	}
}
