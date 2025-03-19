#pragma once
#include "GameObject.h"
#include "PlayerAgent.h"
#include "SnakeBody.h"

class Snake : public GameObject
{
public:
	Snake(PlayerAgent* brain, float speed = 1.0f, int tailStartLength = 2, int x = 0, int y = 0, const std::vector<Tag> tags = { SNAKE }, Color bgColor = WHITE_COLOR, Color patternColor = WHITE_COLOR, char pattern = ' ');
	~Snake() override;

	void Update() override;
	void Render() override;
	void Destroy() override;

	void OnCollision(GameObject* collisionObj) override;

	void MoveTowardsDirection();
	void MoveTail();
	void AddTail(int amount);

private:
	PlayerAgent* brain;

	float speed;
	float speedTimer;

	Vector2 direction;

	std::vector<SnakeBody*> snakeTail; //TO-DO: register these as game objects in the world class
};

