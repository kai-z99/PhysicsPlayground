#include <sstream>

#include "../include/Scene.h"
#include "../include/RectangleObject.h"
#include "../include/CircleObject.h"
#include "../include/LoopObject.h"
#include "../include/DebugDraw.h"
#include "../include/constants.h"
#include "../include/Game.h"
#include "../include/Slider.h"
#include "../include/TextButton.h"
#include "../include/ContactListener.h"
#include "../include/Checkbox.h"


#include <iostream>


Scene::~Scene()
{
	//unload physics objects
	for (PhysicsObject* obj : this->objects)
	{
		this->world->DestroyBody(obj->GetBody());
		delete obj;
		obj = nullptr;
	}

	//unload sliders
	for (Slider* s : this->sliders)
	{
		delete s;
		s = nullptr;
	}

	//unload buttons
	for (TextButton* b : this->buttons)
	{
		delete b;
		b = nullptr;
	}

	delete this->world;
}


void Scene::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(&(lines[0]), lines.size(), sf::Lines);
	this->world->DebugDraw();

	for (PhysicsObject* obj : this->objects)
	{
		obj->Draw(window);
	}

	for (Slider* s : this->sliders)
	{
		s->Draw(window);
	}

	for (TextButton* t : this->buttons)
	{
		t->Draw(window);
	}

	for (Checkbox* c : this->checkboxes)
	{
		c->Draw(window);
	}

	window.draw(this->title);
	this->DrawMouseCoordinates(window);
}

void Scene::DrawMouseCoordinates(sf::RenderWindow& window)
{
	std::ostringstream oss;
	oss.precision(2);
	oss << std::fixed << this->mouseCoordinates.x << "," << this->mouseCoordinates.y;
	std::string position = oss.str();

	sf::Text text = sf::Text(position, *this->game->GetFont(), 20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Mouse::getPosition(window).x + 10.f, sf::Mouse::getPosition(window).y);

	window.draw(text);
}

void Scene::Update(unsigned int frameCount)
{
	this->sceneFramecount++;
	this->mouseCoordinates.x = (float)this->game->GetMousePosition().x / Constants::scale;
	this->mouseCoordinates.y = (float)this->game->GetMousePosition().y / Constants::scale;

	for (PhysicsObject* obj : this->objects)
	{
		obj->Update();
	}


	for (b2Joint* joint : joints)
	{
		if (joint != nullptr)
		{
			switch (joint->GetType())
			{
			case (e_mouseJoint):
				{
					dynamic_cast<b2MouseJoint*>(joint)->SetTarget({ this->mouseCoordinates.x, this->mouseCoordinates.y });
					break;
				}
			}
		}
		
	}

	this->world->Step(1.0f/60.f, 4,8);

	for (Slider* s : this->sliders)
	{
		s->Update(this->game->GetMousePosition(), this->game->GetMouseStatus());
	}

	for (TextButton* t : this->buttons)
	{
		t->Update(this->game->GetMousePosition(), this->game->GetMouseStatus());
	}

	for (Checkbox* c : this->checkboxes)
	{
		c->Update(this->game->GetMousePosition(), this->game->GetMouseStatus());
	}


}

int Scene::GetID() const
{
	return this->id;
}

void Scene::CreateMouseJointOnClick(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping)
{
	bool isButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (this->game->GetMouseStatus() == Click && this->game->GetMousePosition().x < Constants::menuX)
	{
		this->CreateMouseJoint(target, reference, stiffness, damping);
	}

	else if (this->game->GetMouseStatus() == Release)
	{
		//destroy all mosue joints
		for (b2Joint* mj : this->joints)
		{
			if (mj->GetType() == e_mouseJoint)
			{
				this->world->DestroyJoint(mj);
				mj = nullptr;
			}
		}
	}
}

void Scene::CreateMouseJoint(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping)
{
	b2MouseJointDef def;
	def.bodyA = reference->GetBody();
	def.bodyB = target->GetBody();
	def.target = target->GetPosition();
	def.maxForce = 100.0f * target->GetBody()->GetMass();
	def.stiffness = stiffness;
	def.damping = damping;

	b2MouseJoint* mj = (b2MouseJoint*)(this->world->CreateJoint(&def));
	target->GetBody()->SetAwake(true);

	this->joints.push_back(mj);
}



