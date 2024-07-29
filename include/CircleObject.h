#pragma once

#pragma once

#include "PhysicsObject.h"

class CircleObject : public PhysicsObject
{
public:
	//create a circle object centered at position
	CircleObject(b2World& world, const b2Vec2& position, float radius, b2BodyType bodyType, float friction = 0.0f, float restitution = 0.0f, float density = 0.0f);
	~CircleObject();

	void Draw() override;
	void Update() override;

private:
};