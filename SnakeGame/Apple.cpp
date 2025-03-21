#include "Apple.h"

#include "stdafx.h"

Apple::Apple(WorldTile** worldMatrix, int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
: GameObject(worldMatrix, x,y,tags,bgColor,patternColor,pattern), worldMatrix(worldMatrix)
{
	worldMatrix[GetPosition().x][GetPosition().y].tag = Tags::COLLECTABLE_TAG;
}

Apple::~Apple()
{
}

void Apple::Update()
{
	CheckCollision();

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

void Apple::CheckCollision()
{
	if (worldMatrix == nullptr) return;

	if (worldMatrix[GetPosition().x][GetPosition().y].tag == Tags::OBSTACLE_TAG)
		SetRandomPosition();
}

void Apple::SetRandomPosition()
{
	SetPosition(rand() % WORLD_WIDTH, rand() % WORLD_HEIGHT);

	if (worldMatrix == nullptr) return;

	if (worldMatrix[GetPosition().x][GetPosition().y].tag == Tags::OBSTACLE_TAG )
		SetRandomPosition();

	worldMatrix[GetPosition().x][GetPosition().y].tag = Tags::COLLECTABLE_TAG;
}
