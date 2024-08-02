#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Game;
class PhysicsObject;
class DebugDraw;
class Slider;
class TextButton;

class Scene
{
public:
	//Clears and destroys vector pointers and world, removes bodies from world.
	virtual ~Scene();

	//Draws bg lines, debug, objs, sliders, buttons, and mouse coords and title.
	virtual void Draw(sf::RenderWindow& window);

	//update objects etc
	virtual void Update(unsigned int frameCount);


protected:
	Game* game;

	b2World* world;
	std::vector<PhysicsObject*> objects;
	std::vector<b2Joint*> joints;
	std::vector<sf::Vertex> lines;
	std::vector<Slider*> sliders; //temp
	std::vector<TextButton*> buttons;

	
	DebugDraw* debugDraw;
	sf::Vector2f mouseCoordinates;
	sf::Text title;

	void CreateMouseJointOnClick(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping);
	void CreateMouseJoint(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping);

	void DrawMouseCoordinates(sf::RenderWindow& window);

	unsigned int sceneFramecount;
};
