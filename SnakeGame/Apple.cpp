#include "Apple.h"

Apple::Apple(int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
{
	SetPosition(x, y);
	this->tags = tags;
	this->bgColor = bgColor;
	this->patternColor = patternColor;
	this->pattern = pattern;
}

Apple::~Apple()
{
}

void Apple::Update()
{
	GameObject::Update();
}

void Apple::Render()
{
	GameObject::Render();
}

void Apple::Destroy()
{
	GameObject::Destroy();
}
