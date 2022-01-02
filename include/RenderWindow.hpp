#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "Entity.hpp"

class RenderWindow {
public:
	RenderWindow(const char* pTitle, int pWidth, int pHeight);
	void cleanUp();
	SDL_Texture* loadTexture(const char* pFilePath);
	int getRefreshRate();
	void clear();
	void render(Entity& pEntity);
	void render(std::string &m);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};