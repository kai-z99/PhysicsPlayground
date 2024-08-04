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

MomentOfInertia::MomentOfInertia(Game* g)
{
	this->game = g;

	this->world = new b2World({ 0.0f,0.0f });
	this->contactListener = new ContactListener(this);
	this->world->SetContactListener(this->contactListener);
	this->world->SetDebugDraw(this->game->GetDebugDraw());
	this->mouseCoordinates = { (float)this->game->GetMousePosition().x / (float)Constants::scale, (float)this->game->GetMousePosition().y / (float)Constants::scale };
	this->sceneFramecount = 0;
	this->lines = this->game->GetBGLines();
	this->id = 3;

    b2Vec2 position = Constants::worldCenter;

    this->objects.push_back(new RectangleObject(*this->world, { 26.7f, 20.0f }, { 3.0f, 3.0f }, b2_dynamicBody, 0.0f, 0.0f, 100.0f));
    this->objects.push_back(new RevolutionConnectorObject(*this->world, position, this->objects[0]));
    
    this->b = this->objects[0]->GetBody();

    this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.4f, *this->game->GetFont(), "Radius (m)"));

}

MomentOfInertia::~MomentOfInertia()
{

}

void MomentOfInertia::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void MomentOfInertia::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

    static float radius = 3.0f + 20.0f;

    radius = 3.0f + this->sliders[0]->GetProgress() * 20.0f;


    if (this->game->GetMouseStatus() == Hold || this->sceneFramecount == 1)
    {
        static_cast<RevolutionConnectorObject*>(this->objects[1])->SetRadius(*this->world, radius);
    }

    this->sliders[0]->SetValue(radius);
    
    std::cout << static_cast<RevolutionConnectorObject*>(this->objects[1])->GetAngle() << '\n';

    b->ApplyTorque(50000.0f, true);
}
