#include "GameObject.h"
#include "Game.h"
#include <iostream>

GameObject::GameObject(WorldTile** worldMatrix, int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
: position(Vector2(x, y)), prevPosition(position), tags(tags), bgColor(bgColor), patternColor(patternColor), pattern(pattern)
{
}

GameObject::~GameObject()
{
	std::cout << "Deleting game object \n";
}

void GameObject::Update()
{

}

void GameObject::Render()
{
	//derender previous position
	Game::GetInstance().GetGraphics()->ClearPlot(prevPosition.x, prevPosition.y);

	//render my position
	Game::GetInstance().GetGraphics()->PlotTile(position.x, position.y, 10, bgColor, patternColor, pattern);
}

void GameObject::Destroy()
{
	isDestroyed = true;
	//delete this;
}

void GameObject::SetPosition(int x, int y)
{
	prevPosition = position;
	position.x = x;
	position.y = y;
}

void GameObject::SetPosition(Vector2 vector2)
{
	prevPosition = position;
	position = vector2;
}

const Vector2 GameObject::GetPosition()
{
	return position;
}

const Vector2 GameObject::GetPreviousPosition()
{
	return prevPosition;
}

