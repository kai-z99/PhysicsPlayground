#include "../include/DebugDraw.h"
#include "../include/constants.h"
#include "../include/RectangleObject.h"
#include "../include/CircleObject.h"

#include <iostream>
#include <sstream>
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

	


	sf::Text coordinateText = sf::Text();



	b2World world = b2World({0.0f, 9.8f});

	// Setup debug draw with scale
	DebugDraw debugDraw(window, Constants::scale);
	world.SetDebugDraw(&debugDraw);
	//debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);


	CircleObject c = CircleObject(world, { 20,10 }, 1.0f, b2_dynamicBody, 0.8f, 0.2f, 1000.0f);
	RectangleObject ground = RectangleObject(world, { 20,40 }, { 30,1 }, b2_staticBody);

	b2MouseJointDef def;

	def.bodyA = ground.GetBody();
	def.bodyB = c.GetBody();
	def.target = c.GetPosition();
	def.maxForce = 1000.0f * c.GetBody()->GetMass();
	def.stiffness = 5000.0f;
	def.damping = 5000.0f;

	b2MouseJoint* mj = (b2MouseJoint*)world.CreateJoint(&def);
	c.GetBody()->SetAwake(true);

	sf::Font font;
	if (!font.loadFromFile("resources/badFont.ttf"))
	{
		return -1;
	}
	


	while (window.isOpen())
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		float mouseX = static_cast<float>(mousePosition.x) / Constants::scale;
		float mouseY = static_cast<float>(mousePosition.y) / Constants::scale;

		std::ostringstream oss;
		oss.precision(2);
		oss << std::fixed << mouseX << "," << mouseY;
		std::string position = oss.str();

		sf::Text text = sf::Text(position, font, 20);
		text.setFillColor(sf::Color::Black);
		text.setPosition(sf::Mouse::getPosition(window).x + 10.f, sf::Mouse::getPosition(window).y);

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (!mj)
				{
					b2MouseJointDef def;
					def.bodyA = ground.GetBody();
					def.bodyB = c.GetBody();
					def.target = c.GetPosition();
					def.maxForce = 1000.0f * c.GetBody()->GetMass();
					def.stiffness = 5000.0f;
					def.damping = 5000.0f;

					mj = (b2MouseJoint*)world.CreateJoint(&def);
					c.GetBody()->SetAwake(true);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				if (mj)
				{
					world.DestroyJoint(mj);
					mj = nullptr;
				}
			}
		}

		world.Step(1.0f/60.0f, 4, 6);

		if (mj) mj->SetTarget({ mouseX, mouseY });
		c.Update();
		ground.Update();

		

		window.clear(sf::Color::White);
		window.draw(&(lines[0]), lines.size(), sf::Lines);
		world.DebugDraw();
		window.draw(text);
		window.display();
	}


	
	return 0;
}