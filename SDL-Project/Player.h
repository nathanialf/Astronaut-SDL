#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Gun.h"

class Player {
public:
	void render(SDL_Renderer*);
	// Moves the Player
	void move(double);
	// Deallocates texture
	void free();
	// What to do when colliding
	void collide(int);
	// wrap player to other side of screen
	void wrap(int, int);

	bool loadMedia(SDL_Renderer*);
	bool isFloating();

	SDL_Rect* getCollider();
	SDL_Rect* orientors [4];

	// Constructor
	Player();
	// Destructor
	~Player();
private:
	int width;
	int height;
	
	float direction;
	float x;
	float y;
	float velocityX;
	float velocityY;
	float moveSpeed;
	float rotateSpeed;
	float rotationVelocity;
	// TODO:
	float moveAngle;
	float health;

	bool floating;

	LTexture pTexture;

	SDL_Rect* collider;

	Gun* gun;

	// Mutators

	void setWidth(int);
	void setHeight(int);
	void setX(float);
	void setY(float);
	void setVelocityX(float);
	void setVelocityY(float);
	void setMoveSpeed(float);
	void setRotateSpeed(float);
	void setDirection(float);
	void toggleFloating();
	void setCollider(SDL_Rect*);

	// Accessors

	int getWidth();
	int getHeight();
	float getX();
	float getY();
	float getVelocityX();
	float getVelocityY();
	float getMoveSpeed();
	float getRotateSpeed();
	float getDirection();
};