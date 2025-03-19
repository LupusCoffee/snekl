#pragma once
#include "BaseState.h"


struct MenuItem
{
public:
	MenuItem(SnakeGraphics* graphics, const wchar_t* text, Color idleBackgroundColor, Color idleTextColor, Color hoverBackgroundColor, Color hoverTextColor, int height)
		: snakeGraphics(graphics), displayText(text), idleBackgroundColor(idleBackgroundColor), idleTextColor(idleTextColor),
		hoverBackgroundColor(hoverBackgroundColor), hoverTextColor(hoverTextColor), menuHeight(height) {}

	void Render();

	void SetHover(bool _bool);

	void Click();

private:
	SnakeGraphics* snakeGraphics;
	const wchar_t* displayText;
	int menuHeight;

	Color idleBackgroundColor;
	Color idleTextColor;
	Color hoverBackgroundColor;
	Color hoverTextColor;

	bool isHovering = false;
};


class MenuState : public BaseState
{
public:
	MenuState(SnakeGraphics* graphics) : BaseState(graphics) { MenuState::Init(); }

	bool Init() override;
	void Update() override;
	void Render() override;
	void CleanUp() override;

	void KeyDown(int Key) override;

private:
	MenuItem* play = nullptr;
	MenuItem* about = nullptr;
	MenuItem* quit = nullptr;
	int m_menuNav = 0;
	const int m_minNav = 0;
	const int m_maxNav = 2;
};