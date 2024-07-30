#include <sstream>

#include "../include/Scene.h"
#include "../include/RectangleObject.h"
#include "../include/CircleObject.h"
#include "../include/DebugDraw.h"
#include "../include/constants.h"
#include "../include/Game.h"

#include <iostream>


Scene::Scene(Game* g)
{
	this->game = g;
	this->world = new b2World({0.0f,10.0f});
	this->world->SetDebugDraw(this->game->GetDebugDraw());

	this->mouseCoordinates = { (float)this->game->GetMousePosition().x / (float)Constants::scale, (float)this->game->GetMousePosition().y / (float)Constants::scale };

	this->lines = {};

	this->lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, 0), sf::Color::Black));
	this->lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, Constants::screenHeight), sf::Color::Black));

	sf::Color transparentBlack = sf::Color(0, 0, 0, 60);

	for (int i = 0; i <= Constants::screenHeight; i += Constants::scale)
	{
		sf::Vertex horizontalLineP1 = sf::Vertex(sf::Vector2f(0, i), transparentBlack);
		sf::Vertex horizontalLineP2 = sf::Vertex(sf::Vector2f(Constants::menuX, i), transparentBlack);


		this->lines.push_back(horizontalLineP1);
		this->lines.push_back(horizontalLineP2);
	}

	for (int i = 0; i <= Constants::menuX; i += Constants::scale)
	{
		sf::Vertex verticalLineP1 = sf::Vertex(sf::Vector2f(i, 0), transparentBlack);
		sf::Vertex verticalLineP2 = sf::Vertex(sf::Vector2f(i, Constants::screenHeight), transparentBlack);


		this->lines.push_back(verticalLineP1);
		this->lines.push_back(verticalLineP2);
	}

	this->currentScene = 1;

}

void Scene::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(&(lines[0]), lines.size(), sf::Lines);
	this->world->DebugDraw();
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

void Scene::Update()
{
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

	this->UpdateLevelSpecifics(this->currentScene);

	this->world->Step(1.0f/60.f, 8,8);
}

void Scene::UpdateLevelSpecifics(int id)
{
	switch (id)
	{
	case 2:
	{
		//sf::Event event;
		//while ((this->game->GetWindow()->pollEvent(event)))
		//{
		//	std::cout << "in\n";

		//	if (this->game->GetCurrentEvent().type == sf::Event::MouseButtonPressed && this->game->GetCurrentEvent().mouseButton.button == sf::Mouse::Left)
		//	{
		//		PhysicsObject* circle = this->objects[0];
		//		PhysicsObject* tiny = this->objects[2];

		//		this->CreateMouseJoint(circle, tiny);
		//		
		//	}

		//	else if (this->game->GetCurrentEvent().type == sf::Event::MouseButtonReleased && this->game->GetCurrentEvent().mouseButton.button == sf::Mouse::Left)
		//	{
		//		//destroy all mosue joints
		//		for (b2Joint* mj : this->joints)
		//		{
		//			if (mj->GetType() == e_mouseJoint)
		//			{
		//				this->world->DestroyJoint(mj);
		//				mj = nullptr;
		//			}
		//		}
		//	}
		//}

		bool isButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (isButtonPressed && !this->wasButtonPressed)
		{
			PhysicsObject* circle = this->objects[0];
			PhysicsObject* tiny = this->objects[2];

			this->CreateMouseJoint(circle, tiny, 50000.0f, 5000.0f );
		}

		else if (!isButtonPressed && this->wasButtonPressed)
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

		this->wasButtonPressed = isButtonPressed;




		break;
	}
	}


}

void Scene::CreateMouseJoint(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping)
{
	b2MouseJointDef def;
	def.bodyA = reference->GetBody();
	def.bodyB = target->GetBody();
	def.target = target->GetPosition();
	def.maxForce = 1000.0f * target->GetBody()->GetMass();
	def.stiffness = stiffness;
	def.damping = damping;

	b2MouseJoint* mj = (b2MouseJoint*)(this->world->CreateJoint(&def));
	target->GetBody()->SetAwake(true);

	this->joints.push_back(mj);
}



void Scene::SwitchTo(int id)
{
	this->Unload();
	this->Load(id);
	this->currentScene = id;
}


void Scene::Load(int id)
{
	switch (id)
	{
	case 1:
	{
		RectangleObject* r = new RectangleObject(*this->world, { 30.0f, 10.0f }, { 1.0f,1.0f }, b2_dynamicBody, 0.4f, 0.4f, 1000.0f);
		RectangleObject* ground = new RectangleObject(*this->world, { 30.0f, 30.0f }, { 20.0f,1.0f }, b2_staticBody);

		this->objects.push_back(r);
		this->objects.push_back(ground);
		break;
	}

	case 2:
		CircleObject * c = new CircleObject(*this->world, {30.0f, 10.0f}, 2.0f, b2_dynamicBody, 0.5f, 0.5f, 1000.0f);
		RectangleObject* ground = new RectangleObject(*this->world, { 30.0f, 30.0f }, { 20.0f,1.0f }, b2_staticBody);
		RectangleObject* ref = new RectangleObject(*this->world, { 100.0f, 30.0f }, { 0.1f,0.1f }, b2_staticBody);

		this->objects.push_back(c);
		this->objects.push_back(ground);
		this->objects.push_back(ref);
		break;



	}
}

void Scene::Unload()
{
	//unload physics objects
	for (PhysicsObject* obj : this->objects)
	{
		this->world->DestroyBody(obj->GetBody());
		delete obj;
		obj = nullptr;
	}

	this->objects.clear();
}



