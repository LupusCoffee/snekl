#pragma once
#include "GameObject.h"
class Apple : public GameObject
{
public:
	Apple(int x = 0, int y = 0, const std::vector<Tag> tags = { COLLECTABLE }, Color bgColor = WHITE_COLOR, Color patternColor = WHITE_COLOR, char pattern = ' ');
	~Apple() override;

	void Update() override;
	void Render() override;
	void Destroy() override;

	//set position somewhere
};

