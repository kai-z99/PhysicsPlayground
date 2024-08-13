#include "../include/TextButton.h"


TextButton::TextButton(std::string text, const sf::Vector2f& position, const sf::Vector2f& dimensions, const sf::Font& font, sf::Color color, sf::Color outline)
{
	this->position = position;
	this->dimensions = dimensions;
	this->isPressed = false;
	this->isHovering = false;
	this->isHeld = false;

	this->color = color;

	this->rec = sf::RectangleShape(this->dimensions);
	rec.setPosition(this->position);
	rec.setOrigin({ this->dimensions.x / 2, this->dimensions.y / 2 });
	rec.setFillColor(color);
	rec.setOutlineColor(outline);
	rec.setOutlineThickness(5.0f);

	this->sfText = sf::Text(text, font, 50U);
	this->sfText.setFillColor(sf::Color::White);
	this->sfText.setPosition(this->position.x - (sfText.getLocalBounds().width / 2), this->position.y - (sfText.getLocalBounds().height / 2));
}

void TextButton::Update(const sf::Vector2i& mousePos, MouseStatus mouseState)
{
	if (this->rec.getGlobalBounds().contains((sf::Vector2f)mousePos))
	{
		this->isHovering = true;

		if (mouseState == Click)
		{
			this->isPressed = true;
			this->isHeld = true;
		}
		else if (mouseState == Hold)
		{
			this->isHeld = true;
			this->isPressed = false;
		}
		else
		{
			this->isPressed = false;
			this->isHeld = false;
		}
	}
	else
	{
		this->isHovering = false;
		this->isPressed = false;
		this->isHeld = false;
	}

	static const sf::Color lighter = sf::Color::Blue; //temp

	if (this->isPressed) this->rec.setFillColor(sf::Color::Blue);
	else if (this->isHovering) this->rec.setFillColor(sf::Color({ 0, 181, 27, 255}));
	else this->rec.setFillColor(this->color);
}

void TextButton::Draw(sf::RenderWindow& window)
{
	window.draw(this->rec);
	window.draw(this->sfText);
}

void TextButton::SetString(const std::string& string, sf::Font font)
{
	this->sfText.setString(string);
	this->sfText.setPosition(this->position.x - (sfText.getLocalBounds().width / 2), this->position.y - (sfText.getLocalBounds().height / 2));
}

void TextButton::SetFontSize(unsigned int size)
{
	this->sfText.setCharacterSize(size);
	this->sfText.setPosition(this->position.x - (sfText.getLocalBounds().width / 2), this->position.y - (sfText.getLocalBounds().height / 2));
}

bool TextButton::GetIsPressed() const
{
	return this->isPressed;
}

bool TextButton::GetIsHeld() const
{
	return this->isHeld;
}

std::string TextButton::GetString() const
{
	return this->sfText.getString();
}

sf::Vector2f TextButton::GetPosition() const
{
	return this->position;
}
