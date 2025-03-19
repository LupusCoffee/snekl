#include "Apple.h"

Apple::Apple(int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
: GameObject(nullptr, x,y,tags,bgColor,patternColor,pattern)
{
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
