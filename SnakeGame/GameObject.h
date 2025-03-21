#pragma once
#include "InclusionHelper.h"
#include "Tools/RenderHelper.h"
#include "Tools/SnakeGraphics.h"

enum Tag { OBSTACLE, COLLECTABLE, SNAKE };

struct Vector2
{
public:
	Vector2(int x, int y) : x(x), y(y) {};

	int x = 0;
	int y = 0;

	const Vector2 operator+ (const Vector2 vector2)
	{
		return Vector2(x+vector2.x, y+vector2.y);
	}
};

class GameObject
{
public:
	GameObject(WorldTile** worldMatrix = nullptr, int x = 0, int y = 0, const std::vector<Tag> tags = {}, Color bgColor = WHITE_COLOR, Color patternColor = WHITE_COLOR, char pattern = ' ');
	virtual ~GameObject();

	virtual void Update();
	virtual void Render();
	virtual void Destroy();
	bool IsDestroy();

	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Vector2 vector2);
	const Vector2 GetPosition();
	const Vector2 GetPreviousPosition();

protected:
	bool isDestroyed = false;

	Color bgColor;
	Color patternColor;
	char pattern;

	std::vector<Tag> tags;

private:
	Vector2 position;
	Vector2 prevPosition;
};