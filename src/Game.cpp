#include "SFML/Graphics.hpp"
#include "../include/constants.h"
#include "../include/Game.h"
#include "../include/Scene.h"
#include "../include/DebugDraw.h"

#include <iostream>
Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(Constants::screenWidth, Constants::screenHeight), "Box2D Simulation", sf::Style::Default);
	this->debugDraw = new DebugDraw(*window, Constants::scale);

	this->mousePosition = sf::Mouse::getPosition();

	this->font = new sf::Font();
	if (!font->loadFromFile("resources/badFont.ttf"))
	{
		; //font not loaded
	}

	this->scene = new Scene(this);
	this->scene->SwitchTo(4); //temp

	this->frameCount = 0;

	this->mouseStatus = None;
}

Game::~Game()
{
}



void Game::Run()
{
	window->setFramerateLimit(60);
	//func
	while (window->isOpen())
	{
		//update mouse click status
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->mouseStatus = Hold;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->mouseStatus = None;
		}

		while (window->pollEvent(this->currentEvent))
		{
			if (this->currentEvent.type == sf::Event::Closed)
			{
				window->close();
			}

			else if (this->currentEvent.type == sf::Event::MouseButtonPressed && this->currentEvent.mouseButton.button == sf::Mouse::Left)
			{
				this->mouseStatus = Click;
			}

			else if (this->currentEvent.type == sf::Event::MouseButtonReleased && this->currentEvent.mouseButton.button == sf::Mouse::Left)
			{
				this->mouseStatus = Release;
			}
		}

		//switch (this->mouseStatus)
		//{
		//case Hold:
		//	std::cout << "Hold\n";
		//	break;
		//case None:
		//	std::cout << "None\n";
		//	break;
		//case Click:
		//	std::cout << "Click\n";
		//	break;
		//case Release:
		//	std::cout << "Release\n";
		//	break;
		//}
		

		//temp
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->scene->SwitchTo(3);
		}


		this->Update();
		this->Draw();
	}
}

void Game::Draw()
{
	this->scene->Draw(*this->window);

	this->window->display();

}

void Game::Update()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
	this->frameCount++;

	//handle input
	this->scene->Update(this->frameCount);
}

sf::RenderWindow* Game::GetWindow()
{
	return this->window;
}

sf::Vector2i Game::GetMousePosition() const
{
	return this->mousePosition;
}

DebugDraw* Game::GetDebugDraw()
{
	return this->debugDraw;
}

sf::Font* Game::GetFont()
{
	return this->font;
}

sf::Event& Game::GetCurrentEvent()
{
	return this->currentEvent;
}

MouseStatus Game::GetMouseStatus() const
{
	return this->mouseStatus;
}
