#pragma once

#include "Scene.h"

class SimpleHarmonicMotion : public Scene
{
public:
	SimpleHarmonicMotion(Game* g);
	~SimpleHarmonicMotion();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	sf::Text periodText;


};