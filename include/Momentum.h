#pragma once
#include "Scene.h"

class Momentum : public Scene
{
public:
	Momentum(Game* g);
	~Momentum();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:
	b2Vec2 LStartPos;
	b2Vec2 RStartPos;

};