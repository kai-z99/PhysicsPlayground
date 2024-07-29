#include "../include/DebugDraw.h"

DebugDraw::DebugDraw(sf::RenderWindow& window, float scale) : window(window), scale(scale)
{
	this->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit); //temp set all initally
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon = sf::ConvexShape(vertexCount);

	for (int i = 0; i < vertexCount; i++)
	{
		polygon.setPoint(i, sf::Vector2f(vertices[i].x * scale, vertices[i].y * scale));
	}

	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	polygon.setOutlineThickness(1.0f);


	this->window.draw(polygon);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon = sf::ConvexShape(vertexCount);

	for (int i = 0; i < vertexCount; i++)
	{
		polygon.setPoint(i, sf::Vector2f(vertices[i].x * scale, vertices[i].y * scale));
	}

	polygon.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	polygon.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	polygon.setOutlineThickness(1.0f);

	this->window.draw(polygon);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape c = sf::CircleShape(radius * scale);
	c.setPosition(center.x * scale, center.y * scale);
	c.setOrigin(radius * scale, radius * scale);
	c.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	c.setOutlineThickness(1.0f);
	c.setFillColor(sf::Color::Transparent);

	this->window.draw(c);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape c = sf::CircleShape(radius * scale);
	c.setPosition(center.x * scale, center.y * scale);
	c.setOrigin(radius * scale, radius * scale);
	c.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
	c.setOutlineThickness(1.0f);
	c.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

	this->window.draw(c);

	//implement direction vector drwaing soon
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Vertex line[2] =
	{
		sf::Vertex(sf::Vector2f(p1.x * scale,p1.y * scale),sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255)),
		sf::Vertex(sf::Vector2f(p2.x * scale,p2.y * scale),sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255))
	};

	this->window.draw(line, 2, sf::Lines);

}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	sf::CircleShape c = sf::CircleShape(size * scale);
	c.setOrigin(size * scale, size * scale);
	c.setPosition(p.x * scale, p.y * scale);
	c.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));

	this->window.draw(c);

}
