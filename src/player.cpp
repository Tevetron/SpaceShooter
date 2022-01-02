#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Player.hpp"
#include "Bullet.hpp"

#define PI 3.14159265
using namespace std;

Player::Player(Vector2f p_pos, SDL_Texture* p_texture)
:Entity{ p_pos, p_texture } {
	getRotation() = -90;
	right = false;
	left = false;
	up = false;
	down = false;
}

void Player::stopMovement() {
	right = false;
	left = false;
	up = false;
	down = false;
}

void Player::clamp() {
	if(getPos().y < 0)
		getPos().y = 0;
	if(getPos().y > 720 - 16)
		getPos().y = 720 - 16;
	
	if(getPos().x < 0)
		getPos().x = 0;
	if(getPos().x > 1280 - 15)
		getPos().x = 1280 - 15;
}

void Player::keyUp(SDL_KeyboardEvent *event) {
	if(event->repeat == 0) {
		switch(event->keysym.scancode) {
			case SDL_SCANCODE_W: {
				up = false;
				break;		
			}
			case SDL_SCANCODE_A: {
				left = false;
				break;		
			}
			case SDL_SCANCODE_S: {
				down = false;
				break;		
			}
			case SDL_SCANCODE_D: {
				right = false;
				break;		
			}
			default: {
				break;
			}
		}
	}	
}

void Player::keyDown(SDL_KeyboardEvent *event) {
	if(event->repeat == 0) {
		switch(event->keysym.scancode) {
			case SDL_SCANCODE_W: {
				up = true;
				break;		
			}
			case SDL_SCANCODE_A: {
				left = true;
				break;		
			}
			case SDL_SCANCODE_S: {
				down = true;
				break;		
			}
			case SDL_SCANCODE_D: {
				right = true;
				break;		
			}
			default: {
				break;
			}
		}
	}	
}

void Player::shoot(SDL_MouseButtonEvent *event, Bullet &bullets, SDL_Texture* bulletTexture) {
	if(event->button == SDL_BUTTON_LEFT) {
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);	
		float rot = atan2(mouseY - getPos().y, mouseX - getPos().x) - (PI / 2);
		float velY = 20 * std::cos(rot);
		float velX = -20 * std::sin(rot);
		bullets.push(Entity(Vector2f(getPos().x + 7, getPos().y + 6), bulletTexture, velX, velY));
	}
}

void Player::update(const float alpha) {
	int mouseX = 0;
	int mouseY = 0;
	if(up) { getPos().y -= 5 * alpha; }
	if(down) { getPos().y += 5 * alpha; }
	if(left) { getPos().x -= 5 * alpha; }
	if(right) { getPos().x += 5 * alpha; }
	SDL_GetMouseState(&mouseX, &mouseY);
	getRotation() = atan2(mouseY - getPos().y, mouseX - getPos().x) * 180 / PI;
	clamp();
}