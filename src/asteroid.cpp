#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Asteroid.hpp"

Asteroid::Asteroid(Vector2f p_pos, SDL_Texture* p_texture, double p_spin, float p_velocityX, float p_velocityY)
:Entity{ p_pos, p_texture } {
	spin = p_spin;
	velocityX = p_velocityX;
	velocityY = p_velocityY;
}

void Asteroid::wrap() {
	if(getPos().x < 0)
		getPos().x = 1280;
	if(getPos().x > 1280)
		getPos().x = 0;
	if(getPos().y < 0)
		getPos().y = 720;
	if(getPos().y > 720)
		getPos().y = 0;
}

void Asteroid::update() {
	getRotation() += spin;
	getPos().x += velocityX;
	getPos().y += velocityY;
	wrap();
}