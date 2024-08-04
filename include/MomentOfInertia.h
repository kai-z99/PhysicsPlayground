#pragma once

#include "../include/Scene.h"

class MomentOfInertia : public Scene
{

public:
	MomentOfInertia(Game* g);
	~MomentOfInertia();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	b2Body* b;
};