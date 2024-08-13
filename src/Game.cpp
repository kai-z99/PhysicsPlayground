#include "SFML/Graphics.hpp"
#include "../include/constants.h"
#include "../include/Game.h"
#include "../include/CentripetalForce.h"
#include "../include/Momentum.h"
#include "../include/MomentOfInertia.h"
#include "../include/Friction.h"
#include "../include/SimpleHarmonicMotion.h"
#include "../include/Galton.h"
#include "../include/MainMenu.h"
#include "../include/DebugDraw.h"
#include "../include/TextButton.h"
#include <iostream>


#include <iostream>
Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(Constants::screenWidth, Constants::screenHeight), "Box2D Simulation", sf::Style::Fullscreen);
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

	for (int i = 0; i <= 5; i++)
	{
		sf::Texture* texture = new sf::Texture();
		bool success;

		switch (i)
		{
		case 0:
			success = texture->loadFromFile("resources/centripetal.png");
			break;

		case 1:
			success = texture->loadFromFile("resources/momentum.png");
			break;

		case 2:
			success = texture->loadFromFile("resources/momentOfInertia.png");
			break;

		case 3:
			success = texture->loadFromFile("resources/friction3.png");
			break;

		case 4:
			success = texture->loadFromFile("resources/pendulum.png");
			break;

		case 5:
			success = texture->loadFromFile("resources/normal.gif");
			break;

		default:
			success = false;
			break;
		}



		sf::Sprite* sprite = new sf::Sprite(*texture);
		sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);

		this->sprites.push_back(sprite);
	}

	this->backButton = new TextButton("Quit", {Constants::screenWidth - 105.0f, Constants::screenHeight - 55.0f}, {100.0f, 50.0f}, *this->font, sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255));
	this->backButton->SetFontSize(20);
	
}

void Game::Init()
{
	this->scene = new MainMenu(this); //temp
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


		this->Update();
		this->Draw();
	}
}

void Game::Draw()
{
	this->scene->Draw(*this->window);
	this->backButton->Draw(*this->window);
	this->window->display();

}

void Game::Update()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
	this->frameCount++;
	this->backButton->Update(this->mousePosition, this->mouseStatus);

	//one of the scenes
	if (this->scene->GetID() != -1)
	{
		if (this->backButton->GetString() != "Back")
		{
			this->backButton->SetString("Back", *this->font);
		}

		if (this->backButton->GetIsPressed())
		{
			this->ChangeScene(-1);
		}
	}

	//main menu
	else
	{
		if (this->backButton->GetString() != "Quit")
		{
			this->backButton->SetString("Quit", *this->font);
		}

		if (this->backButton->GetIsPressed())
		{
			this->window->close();
		}
	}

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

sf::Sprite* Game::GetSprite(int id)
{
	return this->sprites[id];
}

void Game::ChangeScene(int id)
{
	Scene* newScene;

	switch (id)
	{
	case 0:
		newScene = new CentripetalForce(this);
		break;
	case 1:
		newScene = new Momentum(this);
		break;
	case 2:
		newScene = new MomentOfInertia(this);
		break;
	case 3:
		newScene = new Friction(this);
		break;
	case 4:
		newScene = new SimpleHarmonicMotion(this);
		break;
	case 5:
		newScene = new Galton(this);
		break;
	case -1:
		newScene = new MainMenu(this);
		break;

	default:
		newScene = new CentripetalForce(this);
		break;
	}

	delete this->scene;
	this->scene = newScene;
}
