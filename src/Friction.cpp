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


Friction::Friction(Game* g): Scene(g)
{
	this->world->SetGravity({ 0.0f, 100.0f });
	this->id = 4;

	this->title = sf::Text("Friction", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	this->rampCenterPosition = { 27, Constants::worldCenter.y + 16.0f - 1.0f };

	this->objects.push_back(new RectangleObject(*this->world, Constants::worldCenter + b2Vec2(0.0f, 16.0f), { Constants::menuX / Constants::scale, 2.0f }, b2_staticBody, 0.5f));
	this->objects.push_back(new RampObject(*this->world, this->rampCenterPosition, Constants::PI / 4, 25.0f, b2_staticBody, 0.5f));
	this->objects.push_back(new RampObject(*this->world, this->rampCenterPosition, Constants::PI / 4, 5.0f, b2_staticBody, 0.5f, 0.0f, 0.0f, true));

	this->cubeStartPosition = dynamic_cast<RampObject*>(this->objects[2])->GetPosition() + b2Vec2((25.0f/2.0f) * cosf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()), -(25.0f / 2.0f) * sinf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()));
	this->targetAngle = Constants::PI / 4.0f;

	this->objects.push_back(new RectangleObject(*this->world, this->cubeStartPosition, {3.0f,3.0f}, b2_dynamicBody, 0.5f, 0.0f, 100.0f));
	this->objects[3]->SetAngle(Constants::PI / 4);

	this->ropeConnectorPosition = dynamic_cast<RampObject*>(this->objects[1])->GetTopCornerPosition() + b2Vec2(0.0f, -2.0f);
	this->ropeConnectorPosition += b2Vec2(200.0f * cosf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()), -200.0f * sinf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()));

	this->objects.push_back(new RopeConnectorObject(*this->world, this->ropeConnectorPosition, 0.0f, 1, this->objects[3], 0.0f, 600.0f));
	dynamic_cast<RopeConnectorObject*>(this->objects[4])->SetStiffness(400.0f);

	this->objects.push_back(new RampObject(*this->world, dynamic_cast<RampObject*>(this->objects[1])->GetTopCornerPosition(), Constants::PI / 4, 5.0f, b2_staticBody, 0.5f, 0.0f, 0.0f, true, true));

	//BUTTONS
	this->buttons.push_back(new TextButton("Center Cube", { Constants::menuX + 200, 150 }, { 150,75 }, *this->game->GetFont(), sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255)));
	this->buttons[0]->SetFontSize(20);


	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.5f, *this->game->GetFont(), "Angle (D)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 500 }, 300, 0.5f, *this->game->GetFont(), "Rope Stiffness (N/M)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 700 }, 300, 0.5f, *this->game->GetFont(), "Density (KG/M^2)"));
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 900 }, 300, 0.5f, *this->game->GetFont(), "Friction"));
	
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

	//update startpos of the cube
	this->cubeStartPosition = dynamic_cast<RampObject*>(this->objects[2])->GetPosition() + b2Vec2((25.0f / 2.0f) * cosf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()), -(25.0f / 2.0f) * sinf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()));

	if (this->buttons[0]->GetIsPressed())
	{
		this->objects[3]->SetPosition(this->cubeStartPosition);
	}

	static float angle = this->targetAngle;
	static float stiffness;
	static float density;
	static float friction;

	this->targetAngle = (Constants::PI / 8.0f) + (Constants::PI / 4.0f) * this->sliders[0]->GetProgress();
	stiffness = 20.0f + 1880.0f *this->sliders[1]->GetProgress();
	density = 30.0f + 470.0f * this->sliders[2]->GetProgress();
	friction = this->sliders[3]->GetProgress();


	if (fabsf(angle - targetAngle) > 0.006f || this->sceneFramecount == 1)
	{
		if (angle > this->targetAngle)
		{
			angle -= 0.005f;

		}
		else if (angle < this->targetAngle)
		{
			angle += 0.005f;
		}

		//Set angles of ramps
		dynamic_cast<RampObject*>(this->objects[1])->SetAngle(angle);
		dynamic_cast<RampObject*>(this->objects[2])->SetAngle(Constants::PI / 2.0f - angle);
		dynamic_cast<RampObject*>(this->objects[5])->SetPosition(dynamic_cast<RampObject*>(this->objects[1])->GetTopCornerPosition());
		dynamic_cast<RampObject*>(this->objects[5])->SetAngle(Constants::PI / 2.0f - angle);

		//Set position of rope connector
		this->ropeConnectorPosition = dynamic_cast<RampObject*>(this->objects[1])->GetTopCornerPosition() + b2Vec2(0.0f, -2.0f);
		this->ropeConnectorPosition += b2Vec2(200.0f * cosf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()), -200.0f * sinf(dynamic_cast<RampObject*>(this->objects[1])->GetAngle()));
		dynamic_cast<RopeConnectorObject*>(this->objects[4])->SetAnchorPosition(*this->world, this->ropeConnectorPosition);
	}

	if (this->game->GetMouseStatus() == Hold || this->sceneFramecount == 1)
	{
		dynamic_cast<RopeConnectorObject*>(this->objects[4])->SetStiffness(stiffness);
		this->objects[3]->GetBody()->SetAwake(true);
		this->objects[3]->SetDensity(density);
		this->SetFrictionOnAllObjects(friction);
	}

	this->sliders[0]->SetValue(this->targetAngle * RADTODEG);
	this->sliders[1]->SetValue(stiffness);
	this->sliders[2]->SetValue(density);
	this->sliders[3]->SetValue(friction);

	//if (this->sceneFramecount % 30 == 0)
	//{
	//	std::cout << "TARGET ANGLE : " << this->targetAngle << '\n';
	//	std::cout << "CURRENT ANGLE : " << angle << '\n';
	//	std::cout << "DIFF : " << fabsf(angle - targetAngle) << "> 0.006?\n";
	//}
}

void Friction::SetFrictionOnAllObjects(float friction)
{
	for (b2Contact* contact = world->GetContactList(); contact; contact = contact->GetNext()) {
		if (contact->IsTouching()) 
		{
			contact->SetFriction(friction);
		}
	}

	for (PhysicsObject* obj : this->objects)
	{
		obj->SetFriction(friction);
	}
}

//Draw  a bg white rec to cover rope line or some shi along those lines