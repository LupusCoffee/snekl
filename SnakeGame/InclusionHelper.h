#pragma once

enum class Tags { EMPTY_TAG, COLLECTABLE_TAG, OBSTACLE_TAG };

struct WorldTile
{
	Tags tag;
};