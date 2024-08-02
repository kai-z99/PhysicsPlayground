#pragma once

#include "SFML/Graphics.hpp"
#include "helpers.h"

class Checkbox
{
public:
	Checkbox(const sf::Vector2f& position, bool checked, const std::string& title, const sf::Font& font);
	bool GetIsChecked() const;

	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2i& mousePos, MouseStatus mouseState);
private:
	bool isChecked;

	sf::RectangleShape rec;
	sf::RectangleShape innerRec;
	sf::Text title;
};

//menu