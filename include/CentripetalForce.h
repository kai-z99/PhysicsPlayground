#pragma once

#include "../include/Scene.h"

class CentripetalForce : public Scene
{

public:
	CentripetalForce(Game* g);
	~CentripetalForce();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	b2Vec2 ballStartPosition;
};