#pragma once
#include "PhysicsObject.h"

class RopeConnectorObject : public PhysicsObject
{
public:
	RopeConnectorObject(b2World& world, const b2Vec2& position, float length, int segments, PhysicsObject* attached);
	~RopeConnectorObject();

	void Draw(sf::RenderWindow& window) override;
	void Update() override;

private:
	std::vector<b2Body*> segments;


};