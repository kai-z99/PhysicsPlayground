#include "../include/RopeConnectorObject.h"

RopeConnectorObject::RopeConnectorObject(b2World& world, const b2Vec2& position, float length, int segments, PhysicsObject* attached, float minLength, float maxLength)
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
	jd.maxLength = maxLength; //temp
	jd.minLength = minLength; //temp
	jd.damping = 0.0f;
	jd.stiffness = 0.0f;

	this->joint = (b2DistanceJoint*)world.CreateJoint(&jd);
	this->attached = attached;

	this->length = length;
	this->minLength = minLength;
	this->maxLength = maxLength;
	this->stiffness = 0.0f;
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

void RopeConnectorObject::SetAnchorPosition(b2World& world, const b2Vec2& position)
{
	world.DestroyJoint(this->joint); //remove joint

	//CREATE THE ANCHOR POINT. (THIS IS THE OBJECTS BODY MEMBER)-----------
	this->SetPosition(position); // chagne postion to new position of anchor
	//----------------------------------------------------------------------

	//Recreate joint
	b2DistanceJointDef jd;
	jd.Initialize(this->body, this->attached->GetBody(), this->body->GetWorldCenter(), this->attached->GetBody()->GetWorldCenter());
	jd.length = this->length;
	jd.maxLength = this->maxLength; //temp
	jd.minLength = this->minLength; //temp
	jd.damping = 0.0f;
	jd.stiffness = this->stiffness;

	this->joint = (b2DistanceJoint*)world.CreateJoint(&jd);
}

void RopeConnectorObject::SetStiffness(float stiffness)
{
	this->stiffness = stiffness;
	this->joint->SetStiffness(stiffness);
}
