#pragma once

#include "helpers.h"

class Scene; //EACH SCENE HAS A WORLD AND OBJECTS VEC. COMMON: MENU
class DebugDraw;



class Game
{
public:
	Game();
	~Game();

	void Run();
	void Draw();
	void Update();

	sf::RenderWindow* GetWindow();
	sf::Vector2i GetMousePosition() const;
	DebugDraw* GetDebugDraw();
	sf::Font* GetFont();
	sf::Event& GetCurrentEvent();
	MouseStatus GetMouseStatus() const;

private:
	unsigned int frameCount;

	sf::RenderWindow* window;
	sf::Vector2i mousePosition;

	Scene* scene;
	DebugDraw* debugDraw;
	sf::Font* font;
	sf::Event currentEvent;

	MouseStatus mouseStatus;
};