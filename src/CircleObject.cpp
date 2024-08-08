#include "../include/CircleObject.h"
#include "../include/constants.h"

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
	this->density = density;

	this->body->CreateFixture(&fixture);

	this->position.x = position.x;
	this->position.y = position.y;


	//SFML
	this->circle = sf::CircleShape(radius * Constants::scale);
	this->circle.setFillColor(sf::Color::Magenta);
	this->circle.setOrigin(radius * Constants::scale, radius * Constants::scale);
	this->circle.setPosition(position.x * Constants::scale, position.y * Constants::scale);

	this->lineDesign = sf::RectangleShape({ 5.0f, radius * Constants::scale * 2.0f });
	this->lineDesign.setFillColor(sf::Color::Green);
	this->lineDesign.setOrigin(this->lineDesign.getSize().x / 2, this->lineDesign.getSize().y / 2);
	this->lineDesign.setPosition(this->position.x * Constants::scale, this->position.y * Constants::scale);
	this->lineDesign.setRotation(0);
}

CircleObject::~CircleObject()
{
}

void CircleObject::Draw(sf::RenderWindow& window)
{
	window.draw(this->circle);
	window.draw(this->lineDesign);

}

void CircleObject::Update()
{
	PhysicsObject::Update();

	//sfml
	this->circle.setPosition(this->position.x * Constants::scale, this->position.y * Constants::scale);
	this->lineDesign.setPosition(this->position.x * Constants::scale, this->position.y * Constants::scale);
	this->lineDesign.setRotation(this->angle * (180 / Constants::PI));
}
