#pragma once
#include "PlayerAgent.h"
#include "SnakeBody.h"

class Snake : public GameObject
{
public:
	Snake(WorldTile** worldMatrix = nullptr, PlayerAgent* brain = nullptr, float speed = 1.0f, int tailStartLength = 2, int x = 0, int y = 0, const std::vector<Tag> tags = { SNAKE }, Color bgColor = WHITE_COLOR, Color patternColor = WHITE_COLOR, char pattern = ' ');
	~Snake() override;

	void Update() override;
	void Render() override;
	void Destroy() override;

	void MoveTowardsDirection();
	void SetColliders();
	void CheckCollisions();

	void MoveTail();
	void AddTail(int amount);

	void AddToPosition(int x, int y);
	void AddToPosition(Vector2 vector2);

private:
	SnakeBody* GetLastSnakeTailBody();
	Vector2 GetPrevPosOfLastSnakeTailBody();

	WorldTile** worldMatrix;
	PlayerAgent* brain;

	float speed;
	float speedTimer;

	Vector2 direction;

	std::vector<SnakeBody*> snakeTail;
};

