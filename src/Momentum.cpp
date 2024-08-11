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
#include "../include/ContactListener.h"
#include "../include/Checkbox.h"


#include <iostream>

Momentum::Momentum(Game* g) : Scene(g)
{
	this->world->SetGravity({0.0f, 30.0f});

	this->id = 1;

	this->title = sf::Text("Momentum", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	this->LStartPos = { 35.0f,30.0f };
	this->RStartPos = { 37.0f,30.0f };

	//OBJECTS
	this->objects.push_back(new CircleObject(*this->world, this->LStartPos, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	this->objects.push_back(new RopeConnectorObject(*this->world, { 35.0f, 20.0f }, 10.0f, 3, this->objects[0], 10.0f, 10.0f));

	this->objects.push_back(new CircleObject(*this->world,this->RStartPos, 1.0f, b2_dynamicBody, 0.0f, 1.0f, 300.0f));
	this->objects.push_back(new RopeConnectorObject(*this->world, { 37.0f, 20.0f }, 10.0f, 3, this->objects[2], 10.0f, 10.0f));


	this->objects.push_back(new RectangleObject(*this->world, { 100.0f, 30.0f }, { 0.1f,0.1f }, b2_staticBody));


	//SLIDERS
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.4f, *this->game->GetFont(), "Initial Force (kN)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 500 }, 300, 0.5f, *this->game->GetFont(), "Left Ball Density (KG/M^2)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 700 }, 300, 0.5f, *this->game->GetFont(), "Right Ball Density (KG/M^2)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 900 }, 300, 2.0f/3.0f, *this->game->GetFont(), "Restitution"));

	//BUTTONS
	this->buttons.push_back(new TextButton("GO!", { Constants::menuX + 200, 100 }, { 200,100 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("Reset", { Constants::menuX + 200, 200 }, { 100,50 }, *this->game->GetFont(), sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255)));
	this->buttons[1]->SetFontSize(20);

	//CEHCKBOIXES
	this->checkboxes.push_back(new Checkbox({Constants::menuX + 100, 400}, true, "Enable Mouse Pulling", *this->game->GetFont()));

	
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

	static float impulseStrength = 50000.0f + 5200000.0f;
	static float Ldensity = 50.0f + 950.0f;
	static float Rdensity = 50.0f + 950.0f;
	static float restitution = 1.5f;

	//if go button is pressed, apply force to L ball.
	if (this->buttons[0]->GetIsPressed())
	{
		this->objects[0]->ApplyForce({ -impulseStrength,0.0f });
	}
	//if reseet button is clikced, put balls back in spawn
	else if (this->buttons[1]->GetIsPressed())
	{
		this->objects[0]->SetPosition(this->LStartPos);
		this->objects[0]->SetVelocity({ 0.0f,0.0f });
		this->objects[0]->SetAngularVelocity(0.0f);
		this->objects[0]->SetAngle(0.0f);

		this->objects[2]->SetPosition(this->RStartPos);
		this->objects[2]->SetVelocity({ 0.0f,0.0f });
		this->objects[2]->SetAngularVelocity(0.0f);
		this->objects[2]->SetAngle(0.0f);

	}

	//SLIDERS-----------------------------------------------------
	//update values based on sliders
	impulseStrength = 50000.0f + this->sliders[0]->GetProgress() * 5200000.0f;
	Ldensity = 50.0f + this->sliders[1]->GetProgress() * 950.0f;
	Rdensity = 50.0f + this->sliders[2]->GetProgress() * 950.0f;
	restitution = 1.5 * this->sliders[3]->GetProgress();

	//for friction, just use the sldier value because it happens to be between 0-1.
	this->sliders[0]->SetValue(impulseStrength / 1000.0f); //divide by 1000 to conmvert N to kN
	this->sliders[1]->SetValue(Ldensity);
	this->sliders[2]->SetValue(Rdensity);
	this->sliders[3]->SetValue(restitution);
	//------------------------------------------------------------

	//only apply changes when mosue is release so you dont cahnge body every frame
	if (this->game->GetMouseStatus() == Release || this->sceneFramecount == 1)
	{
		//apply physics based on slider values
		this->objects[0]->SetDensity(Ldensity);
		this->objects[2]->SetDensity(Rdensity);
		
		this->objects[0]->SetRestitution(restitution);
		this->objects[2]->SetRestitution(restitution);
	}

	if (this->checkboxes[0]->GetIsChecked())
	{
		this->CreateMouseJointOnClick(this->objects[0], this->objects[4], Ldensity * 3.0f, 100.f);
	}
}
