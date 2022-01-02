#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>

#include "Entity.hpp"

using namespace std;

class Bullet {
public:
	Bullet();
	void update(const float alpha);
	void push(Entity e) { bullets.push_front(e); }
	unsigned int size() { return bullets.size(); }
	list<Entity>& getList() { return bullets; }
private:
	list<Entity> bullets;
};