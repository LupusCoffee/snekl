#include "Snake.h"

#include "Game.h"

Snake::Snake(PlayerAgent* brain, float speed, int tailStartLength, int x, int y, const std::vector<Tag> tags, Color bgColor, Color patternColor, char pattern)
: GameObject(x,y,tags,bgColor,patternColor, pattern), brain(brain), speed(speed), speedTimer(0), direction(Vector2(0, 1))
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

void Snake::OnCollision(GameObject* collisionObj)
{
	if (collisionObj->IncludesTag(SNAKE) || collisionObj->IncludesTag(OBSTACLE)) Game::GetInstance().SetState(OUTRO_STATE);
	if (collisionObj->IncludesTag(COLLECTABLE))
	{
		AddTail(1);
		collisionObj->Destroy();
		//respawn apple
	}

	GameObject::OnCollision(collisionObj);
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
	}
}

void Snake::AddTail(int amount)
{
	for (int i = 0; i < amount; ++i)
		snakeTail.push_back(new SnakeBody(GetPosition().x, GetPosition().y,RED_COLOR));
}
