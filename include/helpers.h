#pragma once

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

b2Vec2 RotatePoint(b2Vec2& point, b2Vec2 center, float angle);
bool CheckCollisionCirclePoint(const sf::CircleShape& circle, const sf::Vector2i& point);

enum MouseStatus
{
	Click = 0,
	Hold,
	Release,
	None,
};