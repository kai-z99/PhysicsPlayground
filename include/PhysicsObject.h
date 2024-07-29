#pragma once

#include "box2d/box2d.h"


class PhysicsObject
{
public:
	virtual void Draw() = 0;
	virtual void Update();

	void SetPosition(const b2Vec2& pos);
	void SetVelocity(const b2Vec2& vel);
	void SetAcceleration(const b2Vec2& accel);
	void SetAngularVelocity(float vel);
	void SetAngle(float ang);

	b2Vec2 GetPosition() const;
	b2Vec2 GetVelocity() const;
	b2Vec2 GetAcceleration() const;
	float GetAngle() const;
	float GetAngularVelocity() const;


protected:
	b2Body* body;

	float angle;
	float angularVelocity;

	b2Vec2 position;
	b2Vec2 velocity;
	b2Vec2 acceleration;
};