#include "../include/RevolutionConnectorObject.h"
#include "../include/constants.h"
#include <iostream>

RevolutionConnectorObject::RevolutionConnectorObject(b2World& world, const b2Vec2& position, PhysicsObject* target)
{
	this->position = position;
	this->targetObj = target;

	//CREATE THE ANCHOR POINT. (THIS IS THE OBJECTS BODY MEMBER)-----------
	b2BodyDef pointDef;
	pointDef.type = b2_staticBody;
	pointDef.position = position;
	this->body = world.CreateBody(&pointDef);

	b2CircleShape c;
	c.m_radius = 0.1f;

	b2FixtureDef fixture;
	fixture.shape = &c;

	this->body->CreateFixture(&fixture);
	//----------------------------------------------------------------------
	
	float x = this->targetObj->GetPosition().x - this->position.x;
	float y = this->targetObj->GetPosition().y - this->position.y;

	this->radius = sqrtf(x * x + y * y);
	
	b2RevoluteJointDef jd;
	jd.Initialize(this->body, target->GetBody(), this->position);
	jd.collideConnected = false;
	this->joint = (b2RevoluteJoint*)world.CreateJoint(&jd);

	this->angle = this->joint->GetReferenceAngle();
	this->angle = this->targetObj->GetAngle();

}

RevolutionConnectorObject::~RevolutionConnectorObject()
{
}

void RevolutionConnectorObject::Update()
{
	//PhysicsObject::Update();

	this->position = this->body->GetPosition();

	//SET RADIUS
	float x = this->targetObj->GetPosition().x - this->position.x;
	float y = this->targetObj->GetPosition().y - this->position.y;
	this->radius = sqrtf(x * x + y * y);

	//SET ANGLE
	this->angle = this->joint->GetReferenceAngle();
	this->angle = this->targetObj->GetAngle();
	std::cout << "ANGLE: " << this->angle << "\nRADIUS: " << this->radius << '\n';
}

void RevolutionConnectorObject::Draw(sf::RenderWindow& window)
{

}

void RevolutionConnectorObject::SetRadius(b2World& world, float radius)
{
	world.DestroyJoint(this->joint);
	this->joint = nullptr;

	float x = radius * cosf(this->angle);
	float y = radius * sinf(this->angle);

	this->targetObj->SetPosition({ this->position.x + x, this->position.y + y});

	b2RevoluteJointDef jd;
	jd.Initialize(this->body, targetObj->GetBody(), this->position);
	this->joint = (b2RevoluteJoint*)world.CreateJoint(&jd);

	this->radius = radius;

}

float RevolutionConnectorObject::GetRadius() const
{
	return this->radius;
}

float RevolutionConnectorObject::GetAngularVelocity() const
{
	return this->joint->GetJointSpeed();
}
