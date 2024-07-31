#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Game;
class PhysicsObject;
class DebugDraw;
class Slider;

class Scene
{
public:
	Scene(Game* g);
	~Scene();

	void SwitchTo(int id);
	void Shutdown();

	void Draw(sf::RenderWindow& window);
	void Update(unsigned int frameCount);


private:
	Game* game;

	std::vector<PhysicsObject*> objects;
	std::vector<b2Joint*> joints;
	std::vector<sf::Vertex> lines;
	std::vector<Slider*> sliders; //temp

	b2World* world;

	DebugDraw* debugDraw;
	sf::Vector2f mouseCoordinates;

	
	void UpdateLevelSpecifics(int id);

	bool wasButtonPressed = false;

	void CreateMouseJointOnClick(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping);
	void CreateMouseJoint(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping);

	void DrawMouseCoordinates(sf::RenderWindow& window);

	void Unload();
	void Load(int id);

	int currentScene;
	unsigned int sceneFramecount;
};
