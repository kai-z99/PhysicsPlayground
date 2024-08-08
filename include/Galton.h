#pragma once

#include "Scene.h"

class Galton : public Scene
{
public:
	Galton(Game* g);
	~Galton();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	void DrawNormalDistCurve(sf::RenderWindow& window);
};