#include "../include/Momentum.h"

#include "../include/CentripetalForce.h"
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

Momentum::Momentum(Game* g)
{
	this->game = g;
	this->world = new b2World({ 0.0f,10.0f });
	this->world->SetDebugDraw(this->game->GetDebugDraw());
	this->mouseCoordinates = { (float)this->game->GetMousePosition().x / (float)Constants::scale, (float)this->game->GetMousePosition().y / (float)Constants::scale };
	this->sceneFramecount = 0;
	this->lines = this->game->GetBGLines();

	this->title = sf::Text("Momentum", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	//OBJECTS
	this->objects.push_back(new CircleObject(*this->world, {30.0f,30.0f}, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	this->objects.push_back(new RopeConnectorObject(*this->world, { 30.0f, 20.0f }, 10.0f, 3, this->objects[0]));

	this->objects.push_back(new CircleObject(*this->world, { 32.0f,30.0f }, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	this->objects.push_back(new RopeConnectorObject(*this->world, { 32.0f, 20.0f }, 10.0f, 3, this->objects[2]));

	//this->objects.push_back(new CircleObject(*this->world, { 24.0f,30.0f }, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	//this->objects.push_back(new RopeConnectorObject(*this->world, { 24.0f, 20.0f }, 10.0f, 3, this->objects[4]));

	//this->objects.push_back(new CircleObject(*this->world, { 26.0f,30.0f }, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	//this->objects.push_back(new RopeConnectorObject(*this->world, { 26.0f, 20.0f }, 10.0f, 3, this->objects[6]));

	//this->objects.push_back(new CircleObject(*this->world, { 28.0f,30.0f }, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	//this->objects.push_back(new RopeConnectorObject(*this->world, { 28.0f, 20.0f }, 10.0f, 3, this->objects[8]));


	this->objects.push_back(new RectangleObject(*this->world, { 100.0f, 30.0f }, { 0.1f,0.1f }, b2_staticBody));


	//SLIDERS
	//this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.4f, *this->game->GetFont(), "Initial Force (kN)"));
	//this->sliders.push_back(new Slider({ Constants::menuX + 200, 500 }, 300, 0.2f, *this->game->GetFont(), "Ball Density (KG/M^2)"));
	//this->sliders.push_back(new Slider({ Constants::menuX + 200, 700 }, 300, 0.9f, *this->game->GetFont(), "Friction"));

	//BUTTONS
	//this->buttons.push_back(new TextButton("GO!", { Constants::menuX + 200, 100 }, { 200,100 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("Reset", { Constants::menuX + 200, 200 }, { 100,50 }, *this->game->GetFont(), sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255)));
	this->buttons[0]->SetFontSize(20);
}

Momentum::~Momentum()
{
}

void Momentum::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void Momentum::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);
	this->CreateMouseJointOnClick(this->objects[0], this->objects[4], 1000.0f, 100.f);
}
