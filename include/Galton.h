#pragma once

#include "Scene.h"

class CircleObject;

class Galton : public Scene
{
public:
	Galton(Game* g);
	~Galton();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	void DrawNormalDistCurve(sf::RenderWindow& window);

	void CreatePlayArea(int numPegs);
	void DestroyPlayArea();
	void DestroyMarbles();

	std::vector<CircleObject*> marbles; //this is where the balls are stored. Terrain is stored in this->objects.

	int marbleCount;
	bool pouring;
};