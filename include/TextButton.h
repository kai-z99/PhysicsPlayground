#pragma once
#include "SFML/Graphics.hpp"
#include "helpers.h"

class TextButton
{
public:
	TextButton(std::string text, const sf::Vector2f& position, const sf::Vector2f& dimensions, const sf::Font& font, sf::Color color = sf::Color::Green, sf::Color outline = sf::Color({  0, 181, 27, 255 }));

	void Update(const sf::Vector2i& mousePos, MouseStatus mouseState);
	void Draw(sf::RenderWindow& window);

	bool GetIsPressed() const;
	

private:
	bool isPressed;
	bool isHovering;

	sf::Vector2f position;
	sf::Vector2f dimensions;

	sf::RectangleShape rec;
	sf::Text sfText;
	sf::Color color;
};