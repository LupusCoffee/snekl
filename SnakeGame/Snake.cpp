#include "Snake.h"

#include <iostream>

#include "Game.h"

Snake::Snake(WorldTile** worldMatrix, PlayerAgent* brain, float speed, int tailStartLength, int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
: GameObject(worldMatrix, x,y,tags,bgColor,patternColor, pattern), worldMatrix(worldMatrix), brain(brain), speed(speed), speedTimer(0), direction(Vector2(0, 1))
{
	AddTail(tailStartLength);
}
Snake::~Snake()
{
}

void Snake::Update()
{
	direction = brain->GetDirection();
	if (direction.x == 0 && direction.y == 0) return; //if we ain't moving, that means we haven't started, which means we shouldn't do anything

	if (speedTimer < speed) speedTimer += Game::GetInstance().GetDeltaTime();
	else
	{
		MoveTowardsDirection();
		CheckCollisions();
		SetColliders();
		speedTimer = 0;
	}

	GameObject::Update();
}

void Snake::Render()
{
	for (auto snakeBody : snakeTail) snakeBody->Render();
	GameObject::Render();
}

void Snake::Destroy()
{
	//TO-DO: clean up collisions

	for (auto element : snakeTail)
		element->Destroy();

	GameObject::Destroy();
}

void Snake::MoveTowardsDirection()
{
	MoveTail();
	AddToPosition(direction);
}

void Snake::CheckCollisions()
{
	if (worldMatrix == nullptr) return;

	Tags tag = worldMatrix[GetPosition().x][GetPosition().y].tag;

	std::cout << "TAG: " << tag << "\n";

	if ( tag == OBSTACLE_TAG )
	{
		Game::GetInstance().SetState(OUTRO_STATE);
		return;
	}

	if ( tag == COLLECTABLE_TAG )
		AddTail(1);
}

void Snake::SetColliders()
{
	if (worldMatrix == nullptr) return;

	worldMatrix[GetPosition().x][GetPosition().y].tag = OBSTACLE_TAG; //set head collider

	//set snail tail to obstacles
	for (int bodyIndex = snakeTail.size() - 1; -1 < bodyIndex; --bodyIndex)
		worldMatrix[snakeTail[bodyIndex]->GetPosition().x][snakeTail[bodyIndex]->GetPosition().y].tag = OBSTACLE_TAG;

	//set part before snake tail to empty
	worldMatrix[GetPrevPosOfLastSnakeTailBody().x][GetPrevPosOfLastSnakeTailBody().y].tag = EMPTY_TAG;
}

void Snake::MoveTail()
{
	for (int bodyIndex = snakeTail.size()-1; -1 < bodyIndex; --bodyIndex)
	{
		if (bodyIndex == 0) snakeTail[bodyIndex]->SetPosition(GetPosition());
		else
		{
			Vector2 parentBodyPos = snakeTail[bodyIndex - 1]->GetPosition();
			snakeTail[bodyIndex]->SetPosition(parentBodyPos);
		}
	}
}

void Snake::AddTail(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		if (snakeTail.empty())
			snakeTail.push_back(new SnakeBody(GetPreviousPosition().x, GetPreviousPosition().y, RED_COLOR));
		else
			snakeTail.push_back(new SnakeBody(GetPrevPosOfLastSnakeTailBody().x, GetPrevPosOfLastSnakeTailBody().y, RED_COLOR));
	}
}

SnakeBody* Snake::GetLastSnakeTailBody()
{
	return snakeTail[snakeTail.size() - 1];
}

Vector2 Snake::GetPrevPosOfLastSnakeTailBody()
{
	return snakeTail[snakeTail.size() - 1]->GetPreviousPosition();
}

void Snake::AddToPosition(int x, int y)
{
	SetPosition(Vector2(GetPosition()) + Vector2(x, y));
}

void Snake::AddToPosition(Vector2 vector2)
{
	SetPosition(Vector2(GetPosition()) + vector2);
}
