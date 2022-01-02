#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Entity.hpp"
#include "Bullet.hpp"

using namespace std;

class Player : public Entity {
public:
	Player(Vector2f p_pos, SDL_Texture* p_texture);
	void stopMovement();
	void clamp();
	void update(const float alpha);
	void keyUp(SDL_KeyboardEvent *event);
	void keyDown(SDL_KeyboardEvent *event);
	void shoot(SDL_MouseButtonEvent *event, Bullet &bullets, SDL_Texture* bulletTexture);
private:
	bool left, right, up, down;
};