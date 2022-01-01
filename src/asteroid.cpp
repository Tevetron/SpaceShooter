#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Asteroid.hpp"

Asteroid::Asteroid(Vector2f p_pos, SDL_Texture* p_texture)
:Entity{ p_pos, p_texture } {}

void Asteroid::update() {

}