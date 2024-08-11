#include "../include/SimpleHarmonicMotion.h"
#include "../include/Game.h"
#include "../include/RevolutionConnectorObject.h"
#include "../include/CircleObject.h"
#include "../include/Slider.h"
#include "../include/Constants.h"
#include "../include/TextButton.h"


SimpleHarmonicMotion::SimpleHarmonicMotion(Game* g) : Scene(g)
{
	this->world->SetGravity({ 0.0f, 10.0f });
	this->id = 4;

	this->title = sf::Text("Simple Harmonic Motion", *this->game->GetFont(), 50);
	this->title.setPosition({ 20.0f,20.0f });
	this->title.setFillColor(sf::Color::Black);

	//OBJECTS
	this->objects.push_back(new CircleObject(*this->world, Constants::worldCenter + b2Vec2(10.0f, -10.0f), 1.0f, b2_dynamicBody, 0.0f, 0.0f, 100.0f));
	this->objects.push_back(new RevolutionConnectorObject(*this->world, Constants::worldCenter + b2Vec2(0.0f, -10.0f), this->objects[0]));

	//SLIDERS
	this->sliders.push_back(new Slider({ Constants::menuX + 200, 300 }, 300, 8.0f/15.0f, *this->game->GetFont(), "Radius (M)"));

	this->periodText = sf::Text(FloatToRoundedString(0.0f, 3) + " s", *this->game->GetFont(), 24);
	this->periodText.setPosition(Constants::screenWidth / 2.0f - 200.0f, Constants::screenHeight / 2.0f);
	this->periodText.setFillColor(sf::Color::Black);

}

SimpleHarmonicMotion::~SimpleHarmonicMotion()
{
}

void SimpleHarmonicMotion::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(this->periodText);
}

void SimpleHarmonicMotion::Update(unsigned int frameCount)
{
	Scene::Update(frameCount);

	//make this apply torque if it doesnt reach its max height
	if (this->objects[0]->GetAngularVelocity() > 0) this->objects[0]->ApplyTorque(490.0f * (this->objects[0]->GetDensity() / 100.0f));
	else if (this->objects[0]->GetAngularVelocity() < 0) this->objects[0]->ApplyTorque(-490.0f);
	
	//RADIUS CONTROL------------------------------------------------------------------------------
	static float radius;
	radius = 2.0f + 25.0f * this->sliders[0]->GetProgress();
	this->sliders[0]->SetValue(radius);
	if (this->game->GetMouseStatus() == Hold  || this->sceneFramecount == 1)
	{
		dynamic_cast<RevolutionConnectorObject*>(this->objects[1])->SetRadius(*this->world, radius);
	}
	//--------------------------------------------------------------------------------------------

	this->periodText.setString("~" + FloatToRoundedString(2 * Constants::PI * std::sqrt(radius / std::abs(10.0f)), 3) + " s");
}
