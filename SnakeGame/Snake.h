#pragma once
#include "PlayerAgent.h"
#include "SnakeBody.h"

class Snake : public GameObject
{
public:
	Snake(Tags** worldMatrix = nullptr, PlayerAgent* brain = nullptr, float speed = 1.0f, int tailStartLength = 2, int x = 0, int y = 0, const std::vector<Tag> tags = { SNAKE }, Color bgColor = WHITE_COLOR, Color patternColor = WHITE_COLOR, char pattern = ' ');
	~Snake() override;

	void Update() override;
	void Render() override;
	void Destroy() override;

	void MoveTowardsDirection();
	void MoveTail();
	void AddTail(int amount);

	void AddToPosition(int x, int y);
	void AddToPosition(Vector2 vector2);
	void CheckCollision();

private:
	Tags** worldMatrix;
	PlayerAgent* brain;

	float speed;
	float speedTimer;

	Vector2 direction;

	std::vector<SnakeBody*> snakeTail;
};

