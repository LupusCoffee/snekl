#include "GameObject.h"
#include "Game.h"
#include <iostream>

GameObject::GameObject(int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
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
	delete this;
}

bool GameObject::IsDestroy()
{
	return isDestroyed;
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

void GameObject::AddToPosition(int x, int y)
{
	prevPosition = position;
	position.x = position.x + x;
	position.y = position.y + y;
}

void GameObject::AddToPosition(Vector2 vector2)
{
	prevPosition = position;
	position = position + vector2;
}

const Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::AddTag(Tag tag)
{
	tags.push_back(tag);
}

Tag GameObject::GetTag(int index) const
{
	return tags[index];
}

bool GameObject::IncludesTag(Tag tag) const
{
	for (auto element : tags)
		if (element == tag) return true;

	return false;
}

void GameObject::OnCollision(GameObject* collisionObj)
{
}
