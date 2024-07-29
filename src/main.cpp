#include "../include/DebugDraw.h"
#include "../include/constants.h"
#include "../include/RectangleObject.h"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(Constants::screenWidth, Constants::screenHeight), "Box2D Simulation", sf::Style::Default);
	window.setFramerateLimit(60);


	std::vector<sf::Vertex> lines;

	lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, 0), sf::Color::Black));
	lines.push_back(sf::Vertex(sf::Vector2f(Constants::menuX, Constants::screenHeight), sf::Color::Black));

	sf::Color transparentBlack = sf::Color(0,0,0,60);

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



	b2World world = b2World({0.0f, 9.8f});

	// Setup debug draw with scale
	DebugDraw debugDraw(window, Constants::scale);
	world.SetDebugDraw(&debugDraw);
	//debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);

	RectangleObject r = RectangleObject(world, { 20,20 }, {1,2}, b2_dynamicBody, 0.8f, 0.2f, 1000.0f);
	r.SetVelocity({ 0.0f, -5.0f });
	r.SetAngularVelocity(2.0f);
	RectangleObject r2 = RectangleObject(world, { 20,30 }, { 30,3 }, b2_staticBody, 0.4f);
	r2.SetAngle(Constants::PI / 4);


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.Step(1.0f/60.0f, 4, 6);

		r.Update();

		window.clear(sf::Color::White);
		window.draw(&(lines[0]), lines.size(), sf::Lines);
		world.DebugDraw();
		window.display();
	}


	
	return 0;
}