#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <math.h>

#include "Bullet.hpp"

Bullet::Bullet() {
	list<Entity> temp;
	bullets = temp;
}

void Bullet::update() {
	for(auto itr = bullets.begin(); itr != bullets.end(); itr++) {
		(*itr).getPos().x += (*itr).getVX();
		(*itr).getPos().y += (*itr).getVY();
	}
}