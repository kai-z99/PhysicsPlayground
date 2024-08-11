#pragma once

#include "Scene.h"

class MainMenu : public Scene
{

public:
	MainMenu(Game* g);
	~MainMenu();

	void Draw(sf::RenderWindow& window) override;
	void Update(unsigned int frameCount) override;

private:

	void DrawTriangle(sf::RenderWindow& window, const sf::Vector2f& position);
};