#include "../include/RampObject.h"

RampObject::RampObject(b2World& world, const b2Vec2& position, float angle, float length, b2BodyType bodyType, float friction, float restitution, float density, bool flip, bool rotated)
{
	this->flipped = flip;
	this->angle = angle;
	this->length = length;
	this->rotated = rotated;

	b2BodyDef def;
	def.position = position; //BOTTOM CORNER OF THE RAMP IS POSITION
	def.type = bodyType;
	this->body = world.CreateBody(&def);

	b2PolygonShape rampShape;

	this->vertices[0].Set(0.0f, 0.0f);
	this->vertices[1].Set(length * cosf(angle), 0.0f);
	this->vertices[2].Set(length * cosf(angle), -length * sinf(angle));

	if (this->flipped)
	{
		this->vertices[1].x = -this->vertices[1].x;
		this->vertices[2].x = -this->vertices[2].x;
	}

	if (this->rotated)
	{
		this->vertices[1].x = this->vertices[0].x;
		this->vertices[1].y = this->vertices[2].y;
	}

	rampShape.Set(this->vertices, 3);

	b2FixtureDef fixture;
	fixture.shape = &rampShape;
	fixture.friction = friction;
	fixture.restitution = restitution;
	fixture.density = density;

	this->bodyFixture = this->body->CreateFixture(&fixture);

	this->position.x = position.x;
	this->position.y = position.y;
}

RampObject::~RampObject()
{
}

void RampObject::Draw(sf::RenderWindow& window)
{
	//PhysicsObject::Draw(window);
}

void RampObject::Update()
{
	//PhysicsObject::Update();
}

void RampObject::SetAngle(float angle)
{
	this->angle = angle;

	float originalDensity = this->bodyFixture->GetDensity();
	float originalFriction = this->bodyFixture->GetFriction();

	this->body->DestroyFixture(this->bodyFixture);

	b2PolygonShape rampShape;

	this->vertices[0].Set(0.0f, 0.0f);
	this->vertices[1].Set(this->length * cosf(angle), 0.0f);
	this->vertices[2].Set(this->length * cosf(angle), -this->length * sinf(angle));

	if (this->flipped)
	{
		this->vertices[1].x = -this->vertices[1].x;
		this->vertices[2].x = -this->vertices[2].x;
	}

	if (this->rotated)
	{
		this->vertices[1].x = this->vertices[0].x;
		this->vertices[1].y = this->vertices[2].y;
	}


	rampShape.Set(this->vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rampShape;
	fixtureDef.density = originalDensity;
	fixtureDef.friction = originalFriction;

	this->bodyFixture = this->body->CreateFixture(&fixtureDef);
}

b2Vec2 RampObject::GetTopCornerPosition() const
{
	return this->position + this->vertices[2];
}

b2Vec2 RampObject::GetBottomCornerPosition() const
{
	return this->position + this->vertices[1];
}
