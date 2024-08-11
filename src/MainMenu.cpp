#include "../include/MainMenu.h"
#include "../include/TextButton.h"
#include "../include/Game.h"
#include "../include/Constants.h"


MainMenu::MainMenu(Game* g) : Scene(g)
{
	this->id = -1;
	this->buttons.push_back(new TextButton("", { Constants::menuX / 4.0f, 400 }, { 150,75 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { Constants::menuX / 2.0f, 400 }, { 150,75 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { (3.0f * Constants::menuX) / 4.0f, 400 }, { 150,75 }, *this->game->GetFont()));

	this->buttons.push_back(new TextButton("", { Constants::menuX / 4.0f, 900 }, { 150,75 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { Constants::menuX / 2.0f, 900 }, { 150,75 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { (3.0f * Constants::menuX) / 4.0f, 900 }, { 150,75 }, *this->game->GetFont()));

	for (int i = 0; i <= 5; i++)
	{
		this->game->GetSprite(i)->setPosition(this->buttons[i]->GetPosition() + sf::Vector2f(0.0f, -160.0f));
	}

	//this->game->GetSprite(0)->setPosition({100,100});
}

MainMenu::~MainMenu()
{

}

void MainMenu::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	for (int i = 0; i <= 5; i++)
	{
		window.draw(*this->game->GetSprite(i));
	}

	
}

void MainMenu::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i]->GetIsPressed())
		{
			this->game->ChangeScene(i);
		}
	}
	
}
