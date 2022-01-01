#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

struct Vector2f {
	Vector2f()
	:x(0.0f), y(0.0f) {}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y) {}

	void setX(float p_x) {
		x = p_x;
	}

	void setY(float p_y) {
		y = p_y;
	}

	float x, y;
};