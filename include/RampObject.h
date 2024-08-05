#pragma once

#include "PhysicsObject.h"

class RampObject : public PhysicsObject
{
public:
	RampObject(b2World& world, const b2Vec2& position, float angle, float length, b2BodyType bodyType, float friction = 0.0f, float restitution = 0.0f, float density = 0.0f, bool flip = false);
	~RampObject();

	void Draw(sf::RenderWindow& window) override;
	void Update() override;

	void SetAngle(float angle) override;

	b2Vec2 GetTopCornerPosition() const;

private:
	bool flipped;
	float length;

	b2Fixture* bodyFixture;
	b2Vec2 vertices[3];
};