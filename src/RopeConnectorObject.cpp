#include "../include/RopeConnectorObject.h"

RopeConnectorObject::RopeConnectorObject(b2World& world, const b2Vec2& position, float length, int segments, PhysicsObject* attached)
{
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

	b2DistanceJointDef jd;
	jd.Initialize(this->body, attached->GetBody(), this->body->GetWorldCenter(), attached->GetBody()->GetWorldCenter());
	jd.length = length;
	jd.maxLength = length;
	jd.minLength = length;
	jd.damping = 0.0f;
	jd.stiffness = 0.0f;

	world.CreateJoint(&jd);
}

RopeConnectorObject::~RopeConnectorObject()
{

}

void RopeConnectorObject::Draw(sf::RenderWindow& window)
{

}

void RopeConnectorObject::Update()
{
	PhysicsObject::Update();
}
