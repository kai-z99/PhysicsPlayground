#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Game;
class PhysicsObject;
class DebugDraw;

class Scene
{
public:
	Scene(Game* g);
	~Scene();

	void SwitchTo(int id);
	void Shutdown();

	void Draw(sf::RenderWindow& window);
	void Update();


private:
	Game* game;

	std::vector<PhysicsObject*> objects;
	std::vector<b2Joint*> joints;
	std::vector<sf::Vertex> lines;

	b2World* world;

	DebugDraw* debugDraw;
	sf::Vector2f mouseCoordinates;

	
	void UpdateLevelSpecifics(int id);
	bool wasButtonPressed = false;

	void CreateMouseJoint(PhysicsObject* target, PhysicsObject* reference, float stiffness, float damping);

	void DrawMouseCoordinates(sf::RenderWindow& window);

	void Unload();
	void Load(int id);

	int currentScene;

	
};
