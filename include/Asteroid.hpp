#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Entity.hpp"

using namespace std;

class Asteroid : public Entity {
public:
	Asteroid(Vector2f p_pos, SDL_Texture* p_texture);
	void update();
private:
	float velocityX, velocityY;
	int spin;
};