#include "SFML/Graphics.hpp"
#include "../include/constants.h"
#include "../include/Game.h"
#include "../include/Scene.h"
#include "../include/DebugDraw.h"

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
	this->scene->SwitchTo(1); //temp
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
		this->mousePosition = sf::Mouse::getPosition(*this->window);

		while (window->pollEvent(this->currentEvent))
		{
			if (this->currentEvent.type == sf::Event::Closed)
			{
				window->close();
			}

		}

		//temp
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->scene->SwitchTo(2);
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
	//handle input
	this->scene->Update();
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
