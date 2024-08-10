#include "../include/Galton.h"
#include "../include/Game.h"
#include "../include/RevolutionConnectorObject.h"
#include "../include/CircleObject.h"
#include "../include/RectangleObject.h"
#include "../include/RampObject.h"
#include "../include/Slider.h"
#include "../include/Constants.h"
#include "../include/TextButton.h"
#include <cmath>


static b2Vec2 leftWallPosition = { 12.5f, Constants::screenHeight / 2.0f / Constants::scale };
static b2Vec2 rightWallPosition = { Constants::menuX / Constants::scale - 12.5f, Constants::screenHeight / 2.0f / Constants::scale };

static float wallWidth = 2.5f;
static float groundHeight = 3.0f;
static float playAreaX = rightWallPosition.x - leftWallPosition.x;

static float studRadius = 0.1f;
//static int numPegs = 18;
static float pegWidth = 0.2f;
static float pegHeight = 40.0f;



Galton::Galton(Game* g) : Scene(g)
{
	this->world->SetGravity({ 0.0f, 50.0f });
	this->id = 5;

	this->title = sf::Text("Bonus: Normal Distribution", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	this->marbleCount = 0;
	this->pouring = false;

	//OBJECTS
	this->objects.push_back(new RectangleObject(*this->world, 
		{ Constants::worldCenter.x, Constants::screenHeight / Constants::scale - 2.5f }, 
		{ Constants::screenWidth / Constants::scale, groundHeight },
		b2_staticBody));

	//this->objects.push_back(new RectangleObject(*this->world,
	//	{ Constants::worldCenter.x, 2.5 },
	//	{ Constants::screenWidth / Constants::scale, 3.0f },
	//	b2_staticBody));

	//left wall
	this->objects.push_back(new RectangleObject(*this->world,
		leftWallPosition,
		{ wallWidth, Constants::screenHeight / Constants::scale},
		b2_staticBody));

	//right wall
	this->objects.push_back(new RectangleObject(*this->world,
		rightWallPosition,
		{ wallWidth, Constants::screenHeight / Constants::scale },
		b2_staticBody));

	
	this->objects.push_back(new RampObject(*this->world, 
		{ Constants::worldCenter.x - 0.75f, 15.0f }, 
		Constants::PI / 6.0f, 28.0f,
		b2_staticBody, 
		0.0f, 0.3f, 0.0f, true));
	
	this->objects.push_back(new RampObject(*this->world,
		{ Constants::worldCenter.x + 0.75f, 15.0f },
		Constants::PI / 6.0f, 28.0f,
		b2_staticBody,
		0.0f, 0.3f, 0.0f, false));

	this->objects.push_back(new RampObject(*this->world,
		{ rightWallPosition.x, 27.5f },
		Constants::PI / 5.0f, 25.0f,
		b2_staticBody,
		0.0f, 0.3f, 0.0f, true, true));

	this->objects.push_back(new RampObject(*this->world,
		{ leftWallPosition.x, 27.5f },
		Constants::PI / 5.0f, 25.0f,
		b2_staticBody,
		0.0f, 0.3f, 0.0f, false, true));

	//this->objects.push_back(new RectangleObject(*this->world,
	//	Constants::worldCenter + b2Vec2(-2.0f, -11.0f),
	//	{ wallWidth, 2.0f },
	//	b2_staticBody));

	////right wall
	//this->objects.push_back(new RectangleObject(*this->world,
	//	Constants::worldCenter + b2Vec2(2.0f, -11.0f),
	//	{ wallWidth, 2.0f },
	//	b2_staticBody));


	this->CreatePlayArea(20);

	//BUTTONS
	this->buttons.push_back(new TextButton("GO!", { Constants::menuX + 200, 100 }, { 200,100 }, *this->game->GetFont()));
	this->buttons.push_back(new TextButton("Reset", { Constants::menuX + 200, 200 }, { 100,50 }, *this->game->GetFont(), sf::Color(186, 186, 186, 255), sf::Color(84, 83, 83, 255)));
	this->buttons[1]->SetFontSize(20);

	//SLIDERS
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 0.7, *this->game->GetFont(), "Segments"));



}

Galton::~Galton()
{
}

void Galton::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	DrawNormalDistCurve(window);
}

void Galton::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

	if (this->buttons[1]->GetIsPressed())
	{
		this->DestroyMarbles();
		this->pouring = false;
	}

	//Spawn marbles on click
	if (this->buttons[0]->GetIsPressed())
	{
		this->pouring = true;
	}
	if (this->pouring)
	{
		if (this->marbleCount <= 500)
		{
			if (this->sceneFramecount % 3 == 0)
			{
				this->marbles.push_back(new CircleObject(*this->world, { Constants::worldCenter.x + 0.1f, 5.0f }, 0.33, b2_dynamicBody, 0.0f, 0.2f, 10.0f));
				this->marbles.push_back(new CircleObject(*this->world, { Constants::worldCenter.x - 0.1f, 5.0f }, 0.33, b2_dynamicBody, 0.0f, 0.2f, 10.0f));

				this->marbleCount += 2;
			}
		}
		else
		{
			this->pouring = false;
		}
		
	}

	//Update segments
	if (this->game->GetMouseStatus() == Hold || this->sceneFramecount == 1)
	{
		static int segments;
		segments = 10 + this->sliders[0]->GetProgress() * 12;

		this->DestroyPlayArea();
		this->CreatePlayArea(segments);

		this->sliders[0]->SetValue(segments);
	}
}

static float gaussian(float x, float mean, float stddev) {
	return (1 / (stddev * std::sqrt(2 * Constants::PI))) * std::exp(-0.5 * std::pow((x - mean) / stddev, 2));
}

void Galton::DrawNormalDistCurve(sf::RenderWindow& window)
{
	float mean = playAreaX * Constants::scale / 2.0f;
	float stddev = 100.0f;

	sf::VertexArray curve(sf::LineStrip, playAreaX * Constants::scale);

	for (int x = 0; x < playAreaX * Constants::scale; ++x) {
		float y = gaussian(x, mean, stddev);
		float scaledY = (pegHeight / 2) - y * playAreaX * Constants::scale * 80;
		curve[x].position = sf::Vector2f(x + 250, scaledY + (Constants::screenHeight - 100));
		curve[x].color = sf::Color::Blue;
	}

	window.draw(curve);


}

void Galton::CreatePlayArea(int numPegs)
{
	float pegSpacing = (float)playAreaX / (float)((float)numPegs + 1.0f);
	float verticalStudSpacing = 1.0;

	//+0.1 for floating precision 
	for (float i = leftWallPosition.x + pegSpacing; i <= rightWallPosition.x - pegSpacing + 0.1f; i += pegSpacing)
	{
		this->objects.push_back(new RectangleObject(*this->world,
			{ i, Constants::screenHeight / Constants::scale },
			{ pegWidth, pegHeight },
			b2_staticBody));
	}

	float horizontalStudSpacing = (float)playAreaX / (float)((float)20 + 1.0f);

	//+0.1 for floating precision 
	for (float j = 0.0f; j <= 10.0f; j += 1.0f)
	{
		for (float i = leftWallPosition.x + horizontalStudSpacing + (j * (horizontalStudSpacing / 2.0f)); i <= rightWallPosition.x - horizontalStudSpacing - (j * (horizontalStudSpacing / 2.0f)) + 0.1f; i += horizontalStudSpacing)
		{
			this->objects.push_back(new CircleObject(*this->world,
				{ i, (Constants::screenHeight / Constants::scale) - (pegHeight / 2.0f) - 5.0f - (j * verticalStudSpacing) },
				studRadius,
				b2_staticBody));
		}
	}

}

void Galton::DestroyPlayArea()
{
	std::vector<PhysicsObject*> toKeep;

	for (int i = 0; i < this->objects.size(); i++)
	{
		if (i <= 6) // this is the static objects
		{
			toKeep.push_back(this->objects[i]);
		}
		else //destroy pegs and studs
		{
			this->world->DestroyBody(this->objects[i]->GetBody());
			delete this->objects[i];
		}
	}

	this->objects.clear();
	this->objects = toKeep;
}

void Galton::DestroyMarbles()
{
	for (CircleObject* marble : this->marbles)
	{
		this->world->DestroyBody(marble->GetBody());
		delete marble;
	}

	this->marbles.clear();
	this->marbleCount = 0;
}
