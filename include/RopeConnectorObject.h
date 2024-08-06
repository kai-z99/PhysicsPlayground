#pragma once
#include "PhysicsObject.h"

class RopeConnectorObject : public PhysicsObject
{
public:
	RopeConnectorObject(b2World& world, const b2Vec2& position, float length, int segments, PhysicsObject* attached, float minLength, float maxLength);
	~RopeConnectorObject();

	void Draw(sf::RenderWindow& window) override;
	void Update() override;

	void SetAnchorPosition(b2World& world, const b2Vec2& position);
	void SetStiffness(float stiffness);

private:
	std::vector<b2Body*> segments;
	b2DistanceJoint* joint;
	PhysicsObject* attached;
	float length;
	float minLength;
	float maxLength;
	float stiffness;

};