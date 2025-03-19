#include "Snake.h"

#include "Game.h"

Snake::Snake(Tags** worldMatrix, PlayerAgent* brain, float speed, int tailStartLength, int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
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

	if (speedTimer < speed) speedTimer += Game::GetInstance().GetDeltaTime();
	else
	{
		MoveTowardsDirection();
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
	for (auto element : snakeTail)
	{
		element->Destroy();
	}

	GameObject::Destroy();
}

void Snake::MoveTowardsDirection()
{
	//move tail
	MoveTail();

	AddToPosition(direction);
}

void Snake::MoveTail()
{
	for (int bodyIndex = snakeTail.size()-1; -1 < bodyIndex; --bodyIndex)
	{
		if (bodyIndex == 0) 
			snakeTail[bodyIndex]->SetPosition(GetPosition());
		else
		{
			Vector2 parentBodyPos = snakeTail[bodyIndex - 1]->GetPosition();
			snakeTail[bodyIndex]->SetPosition(parentBodyPos);
		}

		//set the previous position of the last part of the tail as empty
	}
}

void Snake::AddTail(int amount)
{
	for (int i = 0; i < amount; ++i)
		snakeTail.push_back(new SnakeBody(GetPosition().x, GetPosition().y,RED_COLOR));
}

void Snake::AddToPosition(int x, int y)
{
	SetPosition(Vector2(GetPosition()) + Vector2(x, y));

	CheckCollision();

	worldMatrix[GetPosition().x][GetPosition().y] = OBSTACLE_TAG; //doesn't work hmmm
}

void Snake::AddToPosition(Vector2 vector2)
{
	SetPosition(Vector2(GetPosition()) + vector2);
	CheckCollision();
}

void Snake::CheckCollision()
{
	if (worldMatrix[GetPosition().x][GetPosition().y] == OBSTACLE_TAG) 
		Game::GetInstance().SetState(OUTRO_STATE);

	if (worldMatrix[GetPosition().x][GetPosition().y] == COLLECTABLE_TAG)
	{
		AddTail(1);
		//somehow get apple and switch its position to another, randomly selected one
	}
}
