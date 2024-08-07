#pragma once

#include "box2d/box2d.h"

namespace Constants
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int menuX = 1520;
	const float scale = 20.0f; //1m = 10px
	const float PI = 3.14159265359f;

	const b2Vec2 worldCenter = { menuX / 2.0f / scale, screenHeight / 2.0f / scale };

}
