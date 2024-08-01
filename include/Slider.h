#pragma once
#include "SFML/Graphics.hpp"
#include "helpers.h"

class Slider
{
public:
	Slider(const sf::Vector2f& position, int length, float initialProgress, const sf::Font& font, std::string label = "LABEL HERE");
	~Slider();

	void Update(sf::Vector2i mousePos, MouseStatus mouseStatus);
	void Draw(sf::RenderWindow& window);

	float GetProgress() const;
	void SetProgress();

private:
	sf::Vector2f position;

	int length; //in px
	float progress; //from 0.0 to 1.0

	sf::CircleShape knob;
	sf::RectangleShape line;
	sf::Text label;

	bool isHeld;

	//sf::Vertex p1;
	//sf::Vertex p2;
};