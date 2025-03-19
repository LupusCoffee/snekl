#include "SnakeBody.h"

SnakeBody::SnakeBody(int x, int y, Color color, const std::vector<Tag> tags)
: GameObject(x,y,tags,color,color,' ')
{
}

SnakeBody::~SnakeBody()
{
}

void SnakeBody::Update()
{
	GameObject::Update();
}

void SnakeBody::Render()
{
	GameObject::Render();
}

void SnakeBody::Destroy()
{
	GameObject::Destroy();
}
