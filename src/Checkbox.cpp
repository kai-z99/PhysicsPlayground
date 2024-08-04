#include "../include/Checkbox.h"

Checkbox::Checkbox(const sf::Vector2f& position, bool checked, const std::string& title, const sf::Font& font)
{
	this->isChecked = checked;

	this->rec = sf::RectangleShape({30.0f,30.0f});
	this->rec.setPosition(position);
	this->rec.setOrigin(15.0f, 15.0f);
	this->rec.setFillColor(sf::Color::Transparent);
	this->rec.setOutlineColor(sf::Color::Black);
	this->rec.setOutlineThickness(3.0f);

	this->innerRec = sf::RectangleShape({ 24.0f,24.0f });
	this->innerRec.setOrigin(12.0f, 12.0f);
	this->innerRec.setPosition(position);
	this->innerRec.setFillColor(sf::Color::Blue);

	this->title = sf::Text(title, font, 15);
	this->title.setPosition(position.x + 20.0f, position.y);
	this->title.setFillColor(sf::Color::Black);
}

bool Checkbox::GetIsChecked() const
{
	return this->isChecked;
}

void Checkbox::Draw(sf::RenderWindow& window)
{
	window.draw(this->rec);
	if (this->isChecked) window.draw(this->innerRec);
	window.draw(this->title);
}

void Checkbox::Update(const sf::Vector2i& mousePos, MouseStatus mouseState)
{
	if (this->rec.getGlobalBounds().contains((sf::Vector2f)mousePos) && mouseState == Click)
	{
		this->isChecked = !this->isChecked;
	}
}
