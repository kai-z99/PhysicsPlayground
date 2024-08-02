#pragma once

#include "box2d/box2d.h"

class Scene;

class ContactListener : public b2ContactListener
{
public:
	ContactListener(Scene* currentScene);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

private:
	Scene* currentScene;
};