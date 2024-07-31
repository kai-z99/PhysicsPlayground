#include "../include/CircleObject.h"


CircleObject::CircleObject(b2World& world, const b2Vec2& position, float radius, b2BodyType bodyType, float friction, float restitution, float density)
{
	b2BodyDef def;
	def.position = position;
	def.type = bodyType;
	this->body = world.CreateBody(&def);

	b2CircleShape circle;
	circle.m_radius = radius;

	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.friction = friction;
	fixture.restitution = restitution;
	fixture.density = density;

	this->body->CreateFixture(&fixture);

	this->position.x = position.x;
	this->position.y = position.y;
}

CircleObject::~CircleObject()
{
}

void CircleObject::Draw()
{
}

void CircleObject::Update()
{
	PhysicsObject::Update();
}
