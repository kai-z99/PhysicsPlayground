#include "../include/LoopObject.h"
#include <vector>

#include "../include/constants.h"

LoopObject::LoopObject(b2World& world, const b2Vec2& position, float radius, int segments, b2BodyType bodyType, float friction, float restitution, float density)
{
	b2BodyDef def;
	def.position = position;
	def.type = bodyType;
	this->body = world.CreateBody(&def);

	b2ChainShape chain;

	std::vector<b2Vec2> points = {};

	float angleBetweenSegments = (2 * Constants::PI) / segments;
	for (int i = 0; i < segments; i++)
	{
		points.push_back({radius * sinf(i * angleBetweenSegments), radius * cosf(i * angleBetweenSegments)});
	}

	chain.CreateLoop(&points[0], segments);

	b2FixtureDef fixture;
	fixture.shape = &chain;
	fixture.friction = friction;
	fixture.restitution = restitution;
	fixture.density = density;

	body->CreateFixture(&fixture);

	this->position.x = position.x;
	this->position.y = position.y;
}

LoopObject::~LoopObject()
{
}

void LoopObject::Draw()
{
}

void LoopObject::Update()
{
	PhysicsObject::Update();
}
