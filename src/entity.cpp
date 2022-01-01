#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

using namespace std;

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture)
:pos(p_pos), texture(p_texture) 
{
	velocityX = 0;
	velocityY = 0;	
	health = 100;
	rotation = 0;
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture, float p_velocityX, float p_velocityY)
:pos(p_pos), texture(p_texture), velocityX(p_velocityX), velocityY(p_velocityY)
{
	health = 100;
	rotation = 0;
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
}