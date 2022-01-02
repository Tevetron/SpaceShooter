#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <experimental/random>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"

using namespace std;

bool collided(Player& player, Asteroid& asteroid) {
	float dx = (player.getPos().x + player.getCurrentFrame().w / 2) 
	- (asteroid.getPos().x + (asteroid.getCurrentFrame().w / 2 + 10));
	float dy = (player.getPos().y + player.getCurrentFrame().h / 2) 
	- (asteroid.getPos().y + (asteroid.getCurrentFrame().h / 2 + 10));
	float distance = sqrt(dx * dx + dy * dy);
	if(distance < 78)
		return true;
	return false;
}

bool collided(Entity& bullet, Asteroid& asteroid) {
	float dx = (bullet.getPos().x) - (asteroid.getPos().x + (asteroid.getCurrentFrame().w / 2 + 10));
	float dy = (bullet.getPos().y) - (asteroid.getPos().y + (asteroid.getCurrentFrame().h / 2 + 10));
	float distance = sqrt(dx * dx + dy * dy);
	if(distance < 70)
		return true;
	return false;
}

bool collided(Entity& e) {
	SDL_Rect rect = e.getCurrentFrame();
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	if(mouseX > e.getPos().x && mouseX < e.getPos().x + rect.w) {
		if(mouseY > e.getPos().y && mouseY < e.getPos().y + rect.h) {
			return true;
		}
	}
	return false;
}

Asteroid generateAsteroid(SDL_Texture* asteroidTexture) {
	int side = rand() % 3;
	Vector2f temp;
	if(side == 0) {
		temp = Vector2f(rand() % (1280 + 160) - 160, -160);
	}
	else if(side == 1) {
		temp = Vector2f(1280, rand() % (720 + 160) - 160);
	}
	else if(side == 2) {
		temp = Vector2f(rand() % (1280 + 160) - 160, 720);
	}
	else {
		temp = Vector2f(-160, rand() % (720 + 160) - 160);
	}

	int velX = (rand() % 10) - 5;
	int velY = (rand() % 10) - 5;
	while(velX == 0)
		velX = (rand() % 10) - 5;
	while(velY == 0)
		velY = (rand() % 10) - 5;
	return Asteroid(
		temp,
		asteroidTexture, 
		(rand() % 8) - 4, 
		velX, 
		velY);	
}

void spawnAsteroids(Player& player, list<Asteroid> &asteroids, SDL_Texture* asteroidTexture, unsigned int num) {
	for(int i = 0; i < (int)num; i++) {
		Asteroid asteroid = generateAsteroid(asteroidTexture);
		while(collided(player, asteroid))
			asteroid = generateAsteroid(asteroidTexture);
		asteroids.push_front(asteroid);
	}
}

int main(int argc, char* args[]) {
	bool begin = true;
	bool gaming = true;
	bool L = false;
	bool hold = true;

	srand(time(0));

	RenderWindow window("SpaceShooter v2.0", 1280, 720);
	SDL_Texture* playerTexture = window.loadTexture("res/gfx/ship.png");
	SDL_Texture* asteroidTexture = window.loadTexture("res/gfx/rock.png");
	SDL_Texture* bulletTexture = window.loadTexture("res/gfx/bullet.png");
	SDL_Texture* backgroundTexture = window.loadTexture("res/gfx/background.jpg");
	SDL_Texture* startTexture = window.loadTexture("res/gfx/start.png");
	SDL_Texture* playagainTexture = window.loadTexture("res/gfx/playagain.png");
	SDL_Texture* quitTexture = window.loadTexture("res/gfx/quit.png");

	Player player(Vector2f(632, 720), playerTexture);
	Entity background(Vector2f(0, 0), backgroundTexture);
	Entity start(Vector2f(576, 240), startTexture);
	Entity play(Vector2f(576, 240), playagainTexture);
	Entity quit(Vector2f(576, 480), quitTexture);
	list<Asteroid> asteroids;
	Bullet bullets;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(begin || hold) {
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;

		while(accumulator >= timeStep) {
			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT: {
						gaming = false;
						begin = false;
						break;
					}
					case SDL_MOUSEBUTTONDOWN: {
						if(collided(start)) {
							begin = false;
						}
						else if(collided(quit)) {
							gaming = false;
							begin = false;
							hold = false;
						}
						break;
					}
					default: {
						break;
					}
				}
			}

			if(begin) {
				window.clear();
				window.render(background);
				window.render(start);
				window.render(quit);
				window.display();
			}
			else {
				if(player.getPos().y > 360) {
					player.getPos().y -= 2;
				}
				else {
					hold = false;
				}
				window.clear();
				window.render(background);
				window.render(player);
				window.display();
			}
			accumulator -= timeStep;
		}
		int frameTicks = SDL_GetTicks() - startTicks;
		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
	}

	while(gaming) {
		unsigned int level = 0;
		while(!begin) {
			if(asteroids.size() <= level / 2) {
				level++;
				spawnAsteroids(player, asteroids, asteroidTexture, level - asteroids.size());
			}

			int startTicks = SDL_GetTicks();
			float newTime = utils::hireTimeInSeconds();
			float frameTime = newTime - currentTime;

			currentTime = newTime;
			accumulator += frameTime;

			while(accumulator >= timeStep) {

				while(SDL_PollEvent(&event)) {
					switch(event.type) {
						case SDL_QUIT: {
							gaming = false;
							begin = true;
							L = false;
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

			const float alpha = accumulator / timeStep;

			player.update(alpha);
			bullets.update(alpha);
			for(auto itr = asteroids.begin(); itr != asteroids.end(); itr++) {
				(*itr).update(alpha);
				if(collided(player, (*itr))) {
					L = true;
					begin = true;
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


			window.clear();
			window.render(background);
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
		while(L) {
			window.clear();
			window.render(play);
			window.render(quit);
			SDL_WaitEvent(&event);
			if(event.type == SDL_QUIT) {
				gaming = false;
				L = false;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN) {
				if(collided(play)) {
					begin = false;
					L = false;
					while(!asteroids.empty())
						asteroids.erase(asteroids.begin());
					player.getPos().x = 632;
					player.getPos().y = 360;
					player.stopMovement();
				}
				else if(collided(quit)) {
					gaming = false;
					L = false;
				}
			}
			window.display();
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}