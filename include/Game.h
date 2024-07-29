#pragma once

class Scene; //EACH SCENE HAS A WORLD AND OBJECTS VEC. COMMON: MENU

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	Scene* currentScene;

};