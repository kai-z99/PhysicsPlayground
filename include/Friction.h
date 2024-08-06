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
	b2Vec2 rampCenterPosition;
	b2Vec2 ropeConnectorPosition;
	b2Vec2 cubeStartPosition;


	float ropeDistance;
	float targetAngle;
};