#include "SFML/Graphics.hpp"
#include "../include/constants.h"
#include "../include/Game.h"
#include "../include/CentripetalForce.h"
#include "../include/Momentum.h"
#include "../include/MomentOfInertia.h"
#include "../include/Friction.h"
#include "../include/SimpleHarmonicMotion.h"
#include "../include/Galton.h"
#include "../include/DebugDraw.h"


#include <iostream>
Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(Constants::screenWidth, Constants::screenHeight), "Box2D Simulation", sf::Style::Default);
	this->debugDraw = new DebugDraw(*window, Constants::scale);

	//MOUSE
	this->mousePosition = sf::Mouse::getPosition();
	this->mouseStatus = None;

	//FONT
	this->font = new sf::Font();
	if (!font->loadFromFile("resources/badFont.ttf"))
	{
		; //font not loaded
	}

	this->frameCount = 0;

	this->scene = nullptr;
	
}

void Game::Init()
{
	this->scene = new Galton(this); //temp
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

			else if (this->currentEvent.type == sf::Event::KeyPressed && this->currentEvent.key.code == sf::Keyboard::Left)
			{
				this->ChangeScene(this->scene->GetID() - 1);
			}

			else if (this->currentEvent.type == sf::Event::KeyPressed && this->currentEvent.key.code == sf::Keyboard::Right)
			{
				this->ChangeScene(this->scene->GetID() + 1);
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

std::vector<sf::Vertex> Game::GetBGLines()
{
	std::vector<sf::Vertex> lines = {};

	lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, 0), sf::Color::Black));
	lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, Constants::screenHeight), sf::Color::Black));

	sf::Color transparentBlack = sf::Color(0, 0, 0, 60);

	for (int i = 0; i <= Constants::screenHeight; i += Constants::scale)
	{
		sf::Vertex horizontalLineP1 = sf::Vertex(sf::Vector2f(0, i), transparentBlack);
		sf::Vertex horizontalLineP2 = sf::Vertex(sf::Vector2f(Constants::menuX, i), transparentBlack);


		lines.push_back(horizontalLineP1);
		lines.push_back(horizontalLineP2);
	}

	for (int i = 0; i <= Constants::menuX; i += Constants::scale)
	{
		sf::Vertex verticalLineP1 = sf::Vertex(sf::Vector2f(i, 0), transparentBlack);
		sf::Vertex verticalLineP2 = sf::Vertex(sf::Vector2f(i, Constants::screenHeight), transparentBlack);


		lines.push_back(verticalLineP1);
		lines.push_back(verticalLineP2);
	}

	return lines;
}

void Game::ChangeScene(int id)
{
	Scene* newScene;

	switch (id)
	{
	case 1:
		newScene = new CentripetalForce(this);
		break;
	case 2:
		newScene = new Momentum(this);
		break;
	case 3:
		newScene = new MomentOfInertia(this);
		break;
	case 4:
		newScene = new Friction(this);
		break;
	case 5:
		newScene = new SimpleHarmonicMotion(this);
		break;
	case 6:
		newScene = new Galton(this);
		break;

	default:
		newScene = new CentripetalForce(this);
		break;
	}

	delete this->scene;
	this->scene = newScene;
}
