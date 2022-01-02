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

void Bullet::update(const float alpha) {
	for(auto itr = bullets.begin(); itr != bullets.end(); itr++) {
		(*itr).getPos().x += (*itr).getVX() * alpha;
		(*itr).getPos().y += (*itr).getVY() * alpha;
	}
}