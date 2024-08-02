#include "../include/ContactListener.h"
#include "../include/Scene.h"

#include <iostream>

ContactListener::ContactListener(Scene* currentScene)
{
	this->currentScene = currentScene;
}

void ContactListener::BeginContact(b2Contact* contact)
{
	switch (this->currentScene->GetID())
	{
	case 1:
	{
		std::cout << "Collision Detected in Scene 1\n";
	}

	case 2:
	{
		std::cout << "Collision Detected in Scene 2\n";
	}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	switch (this->currentScene->GetID())
	{
	case 1:
	{
		std::cout << "Collision Ended in Scene 1\n";
	}

	case 2:
	{
		std::cout << "Collision Ended in Scene 2\n";
	}
	}
}
