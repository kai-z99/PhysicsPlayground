#include "../include/PhysicsObject.h"

void PhysicsObject::Update()
{
	this->position = this->body->GetPosition();
	this->velocity = this->body->GetLinearVelocity();

	this->angle = this->body->GetAngle();
	this->angularVelocity = this->body->GetAngularVelocity();
}

void PhysicsObject::SetPosition(const b2Vec2& pos)
{
	if (this->body)
	{
		this->body->SetTransform(pos, this->body->GetAngle());
	}
	
	this->position = pos;
}

void PhysicsObject::SetVelocity(const b2Vec2& vel)
{
	this->body->SetLinearVelocity(vel);
}

void PhysicsObject::SetAngularVelocity(float vel)
{
	this->body->SetAngularVelocity(vel);
}

void PhysicsObject::SetAngle(float ang)
{
	if (this->body)
	{
		this->body->SetTransform(this->body->GetPosition(), ang);
	}

	this->angle = ang;
}

b2Vec2 PhysicsObject::GetPosition() const
{
	return this->position;
}

b2Vec2 PhysicsObject::GetVelocity() const
{
	return this->velocity;
}

b2Vec2 PhysicsObject::GetAcceleration() const
{
	return this->acceleration;
}

float PhysicsObject::GetAngle() const
{
	return this->angle;
}

float PhysicsObject::GetAngularVelocity() const
{
	return this->angularVelocity;
}
