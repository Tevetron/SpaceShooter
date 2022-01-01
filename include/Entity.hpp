#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Math.hpp"

using namespace std;

class Entity {
public:
	Entity(Vector2f p_pos, SDL_Texture* p_texture);
	Entity(Vector2f p_pos, SDL_Texture* p_texture, float p_velocityX, float p_velocityY);
	Vector2f& getPos() { return pos; }
	float getVX() { return velocityX; }
	float getVY() { return velocityY; }
	SDL_Texture* getTexture() { return texture; }
	SDL_Rect getCurrentFrame() { return currentFrame; }
	double& getRotation() { return rotation; }
private:
	unsigned int health;
	double rotation;
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
	float velocityX;
	float velocityY;
};