#pragma once
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
#include "Tools/RenderHelper.h"
#include "Tools/SnakeGraphics.h"

class SnakeGraphics;

constexpr int WORLD_WIDTH = 60;
constexpr int WORLD_HEIGHT = 60;

const Color BACKGROUND_COLOR = PURE_BLACK_COLOR;
const Color OBSTACLE_COLOR = WHITE_COLOR;
const Color SNAKE_COLOR = RED_COLOR;
const Color APPLE_COLOR = TURQUOISE_COLOR;