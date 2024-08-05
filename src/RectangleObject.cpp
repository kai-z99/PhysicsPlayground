#include "../include/RectangleObject.h"

RectangleObject::RectangleObject(b2World& world, const b2Vec2& position, const b2Vec2& dimensions, b2BodyType bodyType, float friction, float restitution, float density)
{
	b2BodyDef def;
	def.position = position;
	def.type = bodyType;
	this->body = world.CreateBody(&def);

	b2PolygonShape rec;
	rec.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixture;
	fixture.shape = &rec;
	fixture.friction = friction;
	fixture.restitution = restitution;
	fixture.density = density;

	this->body->CreateFixture(&fixture);

	this->position.x = position.x;
	this->position.y = position.y;
	this->angle = angle;
}

RectangleObject::~RectangleObject()
{
}

void RectangleObject::Draw(sf::RenderWindow& window)
{
}

void RectangleObject::Update()
{
	PhysicsObject::Update();
}
