#pragma once

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

class PhysicsObject
{
public:
	virtual ~PhysicsObject();

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update();

	void ApplyForce(b2Vec2 force, b2Vec2 point);
	void ApplyForce(b2Vec2 force);

	void SetPosition(const b2Vec2& pos);
	void SetVelocity(const b2Vec2& vel);
	void SetAcceleration(const b2Vec2& accel);
	void SetAngularVelocity(float vel);
	virtual void SetAngle(float ang);
	void SetDensity(float density);
	void SetFriction(float friction);
	void SetRestitution(float restitution);

	void Refresh(b2World& world);

	b2Vec2 GetPosition() const;
	b2Vec2 GetVelocity() const;
	b2Vec2 GetAcceleration() const;
	float GetAngle() const;
	float GetAngularVelocity() const;
	float GetMass() const;

	b2Body* GetBody() const;


protected:
	b2Body* body;

	float angle;
	float angularVelocity;

	b2Vec2 position;
	b2Vec2 velocity;
	b2Vec2 acceleration;
};