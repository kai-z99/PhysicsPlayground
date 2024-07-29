#pragma once

#include "PhysicsObject.h"

class RectangleObject : public PhysicsObject
{
public:
	//create a rectangle object centered at position
	RectangleObject(b2World& world, const b2Vec2& position, const b2Vec2& dimensions, b2BodyType bodyType, float friction = 0.0f, float restitution = 0.0f, float density = 0.0f);
	~RectangleObject();

	void Draw() override;
	void Update() override;

private:



};