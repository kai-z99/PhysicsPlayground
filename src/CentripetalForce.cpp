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
#include "../include/ContactListener.h"
#include "../include/Checkbox.h"

#include <iostream>

CentripetalForce::CentripetalForce(Game* g) : Scene(g)
{
	this->world->SetGravity({ 0.0f, 10.0f });

	this->id = 1;

	this->title = sf::Text("Centripetal Force", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	//OBJECTS
	LoopObject* loop = new LoopObject(*this->world, { Constants::menuX / Constants::scale / 2.0f, 30.0f }, 10.0f, 50, b2_staticBody, 0.9f);
	this->objects.push_back(loop);

	this->ballStartPosition = { loop->GetPosition().x, loop->GetPosition().y + 10.0f - 1.0f };

	CircleObject* c = new CircleObject(*this->world, this->ballStartPosition, 1.0f, b2_dynamicBody, 0.9f, 0.4f, 100.0f);
	this->objects.push_back(c);

	RectangleObject* ref = new RectangleObject(*this->world, { 100.0f, 30.0f }, { 0.1f,0.1f }, b2_staticBody);
	this->objects.push_back(ref);

	//SLIDERS
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.4f, *this->game->GetFont(), "Initial Force (kN)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 500 }, 300, 0.2f, *this->game->GetFont(), "Ball Density (KG/M^2)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 700 }, 300, 0.9f, *this->game->GetFont(), "Friction"));
	
	//BUTTONS
	this->buttons.push_back(new TextButton("GO!", { Constants::menuX + 200, 100 }, { 200,100 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("Reset", { Constants::menuX + 200, 200 }, { 100,50 }, *this->game->GetFont(), sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255)));
	this->buttons[1]->SetFontSize(20);

	//CEHCKBOIXES
	this->checkboxes.push_back(new Checkbox({ Constants::menuX + 100, 400 }, true, "Enable Mouse Pulling", *this->game->GetFont()));
}

CentripetalForce::~CentripetalForce()
{
}

void CentripetalForce::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void CentripetalForce::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

	//CENTRIPETAL FORCE SPECIFIC
	static float impulseStrength = 50000.0f + 5200000.0f;
	static float density = 50.0f + 950.0f;

	//toggle?
	if (this->checkboxes[0]->GetIsChecked()) this->CreateMouseJointOnClick(this->objects[1], this->objects[2], 1000.0f, 100.f);


	//BUTTONS------------------------------------------------------
	//if go button is pressed, apply force to ball.
	if (this->buttons[0]->GetIsPressed())
	{
		this->objects[1]->ApplyForce({ impulseStrength,0.0f });
	}
	//if reseet button is clikced, put ball back in spawn
	else if (this->buttons[1]->GetIsPressed())
	{
		this->objects[1]->SetPosition(this->ballStartPosition);
		this->objects[1]->SetVelocity({0.0f,0.0f});
		this->objects[1]->SetAngularVelocity(0.0f);
		this->objects[1]->SetAngle(0.0f);
	}
	//------------------------------------------------------------
	
	//SLIDERS-----------------------------------------------------
	//update values based on sliders
	impulseStrength = 50000.0f + this->sliders[0]->GetProgress() * 5200000.0f;
	density = 50.0f + this->sliders[1]->GetProgress() * 950.0f;
	//for friction, just use the sldier value because it happens to be between 0-1.

	//update the value display on the sliders
	this->sliders[0]->SetValue(impulseStrength / 1000.0f); //divide by 1000 to conmvert N to kN
	this->sliders[1]->SetValue(density);
	this->sliders[2]->SetValue(this->sliders[2]->GetProgress());
	//------------------------------------------------------------

	//only apply changes when mosue is release so you dont cahnge body every frame
	if (this->game->GetMouseStatus() == Release || this->sceneFramecount == 1)
	{
		//apply physics based on slider values
		this->objects[1]->SetDensity(density);
		this->objects[1]->SetFriction(this->sliders[2]->GetProgress());
		this->objects[0]->SetFriction(this->sliders[2]->GetProgress());
	}

}
