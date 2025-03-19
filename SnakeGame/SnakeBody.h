#pragma once
#include "GameObject.h"
class SnakeBody : public GameObject
{
public:
	SnakeBody(int x = 0, int y = 0, Color color = WHITE_COLOR, const std::vector<Tag> tags = { SNAKE });
	~SnakeBody() override;

	void Update() override;
	void Render() override;
	void Destroy() override;
};

