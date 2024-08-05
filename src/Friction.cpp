#include "../include/Friction.h"
#include "../include/Game.h"
#include "../include/DebugDraw.h"
#include "../include/constants.h"
#include "../include/Slider.h"
#include "../include/TextButton.h"
#include "../include/PhysicsObject.h"
#include "../include/RectangleObject.h"
#include "../include/CircleObject.h"
#include "../include/LoopObject.h"
#include "../include/RopeConnectorObject.h"
#include "../include/ContactListener.h"
#include "../include/Checkbox.h"
#include "../include/RevolutionConnectorObject.h"
#include "../include/RampObject.h"

#include <iostream>


Friction::Friction(Game* g)
{
	this->game = g;

	this->world = new b2World({ 0.0f,10.0f });
	this->contactListener = new ContactListener(this);
	this->world->SetContactListener(this->contactListener);
	this->world->SetDebugDraw(this->game->GetDebugDraw());
	this->mouseCoordinates = { (float)this->game->GetMousePosition().x / (float)Constants::scale, (float)this->game->GetMousePosition().y / (float)Constants::scale };
	this->sceneFramecount = 0;
	this->lines = this->game->GetBGLines();
	this->id = 4;

	this->title = sf::Text("Friction", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	this->objects.push_back(new RectangleObject(*this->world, Constants::worldCenter + b2Vec2(0.0f, 16.0f), { Constants::menuX / Constants::scale, 2.0f }, b2_staticBody, 0.5f));
	this->objects.push_back(new RampObject(*this->world, { 27,Constants::worldCenter.y + 16.0f - 1.0f }, Constants::PI / 4, 25.0f, b2_staticBody, 0.5f));
	this->objects.push_back(new RampObject(*this->world, { 27,Constants::worldCenter.y + 16.0f - 1.0f }, Constants::PI / 4, 5.0f, b2_staticBody, 0.5f, 0.0f, 0.0f, true));
	this->objects.push_back(new RectangleObject(*this->world, { this->objects[1]->GetPosition().x + 25 * cosf(Constants::PI / 4.0f) - 1, this->objects[1]->GetPosition().y + 25 * -sinf(Constants::PI / 4.0f) }, {3.0f,3.0f}, b2_dynamicBody, 0.5f, 0.0f, 100.0f));
	this->objects[3]->SetAngle(Constants::PI / 4);



	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.5f, *this->game->GetFont(), "Angle (R)"));
	

}

Friction::~Friction()
{
}

void Friction::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void Friction::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

	static float angle = (Constants::PI / 6.0f) + (Constants::PI / 6.0f) * this->sliders[0]->GetProgress();

	angle = (Constants::PI / 8.0f) + (Constants::PI / 4.0f) * this->sliders[0]->GetProgress();

	if (this->game->GetMouseStatus() == Hold)
	{
		dynamic_cast<RampObject*>(this->objects[1])->SetAngle(angle);
		dynamic_cast<RampObject*>(this->objects[2])->SetAngle(Constants::PI / 2.0f - angle);
	}

	this->sliders[0]->SetValue(angle * RADTODEG);
}

//Change rope connector joint to allow differnet lengths
//Add top corner ramp to friction sim
// add rope connector on that top corner ramp
//possibly add a "targetAngle" system to manage angle changing speed