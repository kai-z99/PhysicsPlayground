#include "../include/MainMenu.h"
#include "../include/TextButton.h"
#include "../include/Game.h"
#include "../include/Constants.h"


MainMenu::MainMenu(Game* g) : Scene(g)
{
	this->id = -1;
	this->buttons.push_back(new TextButton("", { Constants::menuX / 4.0f, 400 }, { 125,60 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { Constants::menuX / 2.0f, 400 }, { 125,60 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { (3.0f * Constants::menuX) / 4.0f, 400 }, { 125,60 }, *this->game->GetFont()));

	this->buttons.push_back(new TextButton("", { Constants::menuX / 4.0f, 900 }, { 125,60 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { Constants::menuX / 2.0f, 900 }, { 125,60 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("", { (3.0f * Constants::menuX) / 4.0f, 900 }, { 125,60 }, *this->game->GetFont()));

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
		this->DrawTriangle(window, this->buttons[i]->GetPosition());
		sf::Text title = sf::Text("", *this->game->GetFont(), 30);

		switch (i)
		{
		case 0:
			title.setString("Centripetal Force");
			break;
		case 1:
			title.setString("Momentum");
			break;
		case 2:
			title.setString("Moment of Inertia");
			break;
		case 3:
			title.setString("Friction");
			break;
		case 4:
			title.setString("Harmonic Motion");
			break;
		case 5:
			title.setString("Normal Distribution");
			break;
		}

		title.setPosition(this->buttons[i]->GetPosition() + sf::Vector2f(-(title.getLocalBounds().width / 2.0f), 70.0f));
		title.setFillColor(sf::Color::Black);

		
		window.draw(title);

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

void MainMenu::DrawTriangle(sf::RenderWindow& window, const sf::Vector2f& position)
{
	sf::VertexArray triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = position + sf::Vector2f(-12.0f, -10.0f);
	triangle[1].position = position + sf::Vector2f(-12.0f,  10.0f);
	triangle[2].position = position + sf::Vector2f(12.0f, 0.0f);
	
	sf::Color fillColor = sf::Color::White;
	triangle[0].color = fillColor;
	triangle[1].color = fillColor;
	triangle[2].color = fillColor;

	window.draw(triangle);
}
