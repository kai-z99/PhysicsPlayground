#pragma once

#include "PhysicsObject.h"

class LoopObject : public PhysicsObject
{
public:
	//create a rectangle object centered at position
	LoopObject(b2World& world, const b2Vec2& position, float radius, int segments, b2BodyType bodyType, float friction = 0.0f, float restitution = 0.0f, float density = 0.0f);
	~LoopObject();

	void Draw() override;
	void Update() override;

private:

};