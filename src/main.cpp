#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"

using namespace std;

bool collided(Player& player, Asteroid& asteroid) {
	float dx = (player.getPos().x + 8) - (asteroid.getPos().x + 70);
	float dy = (player.getPos().y + 8) - (asteroid.getPos().y + 70);
	float distance = sqrt(dx * dx + dy * dy);
	if(distance < 78)
		return true;
	return false;
}

bool collided(Entity& bullet, Asteroid& asteroid) {
	float dx = (bullet.getPos().x) - (asteroid.getPos().x + 70);
	float dy = (bullet.getPos().y) - (asteroid.getPos().y + 70);
	float distance = sqrt(dx * dx + dy * dy);
	if(distance < 70)
		return true;
	return false;
}

int main(int argc, char* args[]) {
	
	RenderWindow window("SpaceShooter v2.0", 1280, 720);
	SDL_Texture* playerTexture = window.loadTexture("res/gfx/ship.png");
	SDL_Texture* asteroidTexture = window.loadTexture("res/gfx/rock.png");
	SDL_Texture* bulletTexture = window.loadTexture("res/gfx/bullet.png");

	Player player(Vector2f(640, 360), playerTexture);
	list<Asteroid> asteroids;
	Bullet bullets;
	for(int i = 0; i < 6; i++) {
		Asteroid asteroid(Vector2f(rand() % (1280 - 160), rand() % (720 - 160)), asteroidTexture);
		asteroids.push_back(asteroid);
	}
	bool gaming = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(gaming) {
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		while(accumulator >= timeStep) {
			player.update();
			bullets.update();
			for(auto itr = asteroids.begin(); itr != asteroids.end(); itr++) {
				(*itr).update();
				if(collided(player, (*itr))) {

				}
			}
			for(auto itr = bullets.getList().begin(); itr != bullets.getList().end(); itr++) {
				for(auto it = asteroids.begin(); it != asteroids.end(); it++) {
					if(collided((*itr), (*it))) {
						it = asteroids.erase(it);
						itr = bullets.getList().erase(itr);
					}
				}
			}

			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: {
						gaming = false;
						break;
					}
					case SDL_KEYDOWN: {
						player.keyDown(&event.key);
						break;
					}
					case SDL_KEYUP: {
						player.keyUp(&event.key);
						break;
					}
					case SDL_MOUSEBUTTONDOWN: {
						player.shoot(&event.button, bullets, bulletTexture);
						break;
					}
					default: {
						break;
					}
				}
			}
			accumulator -= timeStep;
		}

		//const float alpha = accumulator / timeStep;

		window.clear();
		for(auto itr = asteroids.begin(); itr != asteroids.end(); itr++)
			window.render(*itr);
		for(auto itr = bullets.getList().begin(); itr != bullets.getList().end(); itr++)
			window.render(*itr);
		window.render(player);
		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}