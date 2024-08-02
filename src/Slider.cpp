#include "../include/Slider.h"
#include "../include/helpers.h"


Slider::Slider(const sf::Vector2f& position, int length, float initialProgress, const sf::Font& font, std::string label, float value)
{
	this->progress = initialProgress;
	this->length = length;
	this->position = position;

	this->knob = sf::CircleShape(10.0f);
	this->knob.setPosition(this->position.x - (this->length / 2) + (this->progress * this->length), this->position.y);
	this->knob.setOrigin(10.0f, 10.0f);
	this->knob.setFillColor(sf::Color::Blue);

	this->line = sf::RectangleShape({ (float)this->length, 7.5f });
	line.setPosition(this->position);
	line.setOrigin(line.getSize().x / 2, line.getSize().y / 2);
	line.setFillColor(sf::Color::Black);

	this->isHeld = false;


	this->label = sf::Text(label, font, 22U);
	this->label.setFillColor(sf::Color::Black);
	this->label.setPosition(this->position.x - (this->label.getLocalBounds().width / 2), this->position.y - (this->label.getLocalBounds().height / 2) - 40.0f);

	this->value = sf::Text(FloatToRoundedString(value), font, 22U);
	this->value.setFillColor(sf::Color::Black);
	this->value.setPosition(this->position.x - (this->value.getLocalBounds().width / 2), this->position.y - (this->label.getLocalBounds().height / 2) + 40.0f);
}

Slider::~Slider()
{
}

void Slider::Update(sf::Vector2i mousePos, MouseStatus mouseStatus)
{
	//if mouse is over knob
	if (CheckCollisionCirclePoint(this->knob, mousePos) && mouseStatus == Click)
	{
		this->isHeld = true;
	}

	if (this->isHeld && mouseStatus == Release)
	{
		this->isHeld = false;
	}

	if (this->isHeld)
	{
		this->knob.setPosition(mousePos.x, this->position.y);

		//make sure its not too far right or left
		if (this->knob.getPosition().x > this->position.x + (this->length / 2))
		{
			this->knob.setPosition(this->position.x + (this->length / 2), this->position.y);
		}
		else if (this->knob.getPosition().x < this->position.x - (this->length / 2))
		{
			this->knob.setPosition(this->position.x - (this->length / 2), this->position.y);
		}

		//calculates the progreess based on knob and bar position. process is to "squeeze bar to left side of screen" for easy calculation
		this->progress = (knob.getPosition().x - (position.x - (length / 2))) / length;

	}

	//red on the end cases, light blue while pending
	if (this->progress >= 1.0f || this->progress <= 0.0f) this->knob.setFillColor(sf::Color::Red);
	else if (this->isHeld) this->knob.setFillColor(sf::Color::Cyan);
	else this->knob.setFillColor(sf::Color::Blue);

}

void Slider::Draw(sf::RenderWindow& window)
{
	window.draw(this->line);
	window.draw(this->knob);
	window.draw(this->label);
	window.draw(this->value);
}

float Slider::GetProgress() const
{
	return this->progress;
}

void Slider::SetProgress()
{
}

void Slider::SetValue(float value)
{

	this->value.setString(FloatToRoundedString(value));

	//cetner it
	this->value.setPosition(this->position.x - (this->value.getLocalBounds().width / 2), this->position.y - (this->label.getLocalBounds().height / 2) + 40.0f);
}
