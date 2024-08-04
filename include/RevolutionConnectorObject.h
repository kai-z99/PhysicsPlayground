#pragma once

#include "PhysicsObject.h"

class RevolutionConnectorObject : public PhysicsObject
{
public:
	RevolutionConnectorObject(b2World& world, const b2Vec2& position, PhysicsObject* target);
	~RevolutionConnectorObject();

	void Update() override;
	void Draw(sf::RenderWindow& window) override;

	void SetRadius(b2World& world, float radius);
	float GetRadius() const;

	float GetAngularVelocity() const;

private:
	float radius;
	b2RevoluteJoint* joint;
	PhysicsObject* targetObj;
};