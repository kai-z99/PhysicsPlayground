#include "../include/MomentOfInertia.h"
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

#include <iostream>

MomentOfInertia::MomentOfInertia(Game* g) : Scene(g)
{
    this->world->SetGravity({ 0.0f, 0.0f });
	this->id = 3;

    this->title = sf::Text("Moment of Inertia", *this->game->GetFont(), 50);
    this->title.setPosition({ 20.0f,20.0f });
    this->title.setFillColor(sf::Color::Black);

    b2Vec2 position = Constants::worldCenter;
    this->objects.push_back(new RectangleObject(*this->world, { 26.7f, 20.0f }, { 3.0f, 3.0f }, b2_dynamicBody, 0.0f, 0.0f, 100.0f));
    this->objects.push_back(new RevolutionConnectorObject(*this->world, position, this->objects[0]));

    this->b = this->objects[0]->GetBody();

    this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.4f, *this->game->GetFont(), "Radius (M)"));
    this->sliders.push_back(new Slider({ Constants::menuX + 200, 500 }, 300, 0.4f, *this->game->GetFont(), "Torque (Nm)"));
    this->sliders.push_back(new Slider({ Constants::menuX + 200, 700 }, 300, 0.4f, *this->game->GetFont(), "Density (KG/M^2)"));

    this->speedText = sf::Text(FloatToRoundedString(0.0f,3) + " rad/s", *this->game->GetFont(), 24);
    this->speedText.setPosition(Constants::screenWidth / 2.0f - 200.0f, Constants::screenHeight / 2.0f);
    this->speedText.setFillColor(sf::Color::Black);

}

MomentOfInertia::~MomentOfInertia()
{

}

void MomentOfInertia::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
    window.draw(this->speedText);
}

void MomentOfInertia::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

    static float radius = 3.0f + 20.0f;
    static float torque = 1000.0f + 199000.0f;
    static float density = 10.0f + 490.0f;

    radius = 3.0f + this->sliders[0]->GetProgress() * 20.0f;
    torque = 1000.0f + this->sliders[1]->GetProgress() * 199000.0;
    density = 10.0f + this->sliders[2]->GetProgress() * 490.0;

    //dont want to do it unnessisariliy
    if (this->game->GetMouseStatus() == Hold || this->game->GetMouseStatus() == Click || this->sceneFramecount == 1)
    {
        static_cast<RevolutionConnectorObject*>(this->objects[1])->SetRadius(*this->world, radius);
        this->objects[0]->SetDensity(density);
    }

    this->sliders[0]->SetValue(radius);
    this->sliders[1]->SetValue(torque);
    this->sliders[2]->SetValue(density);

    b->ApplyTorque(torque, true);

    this->speedText.setString(FloatToRoundedString(static_cast<RevolutionConnectorObject*>(this->objects[1])->GetAngularVelocity(), 3) + " rad/s");
}
