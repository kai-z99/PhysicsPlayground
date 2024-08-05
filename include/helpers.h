#pragma once

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "constants.h"

b2Vec2 RotatePoint(b2Vec2& point, b2Vec2 center, float angle);
bool CheckCollisionCirclePoint(const sf::CircleShape& circle, const sf::Vector2i& point);
std::string FloatToRoundedString(float f, int decimals);
//bool CheckCollisionRecPoint(const sf::RectangleShape& rec, const sf::Vector2i& point);

extern float RADTODEG;


enum MouseStatus
{
	Click = 0,
	Hold,
	Release,
	None,
};