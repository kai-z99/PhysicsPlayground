#pragma once

#include "Scene.h"

class Friction : public Scene
{
public:
	Friction(Game* g);
	~Friction();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:

};