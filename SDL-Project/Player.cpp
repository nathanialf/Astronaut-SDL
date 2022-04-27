#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include "Player.h"

const bool DEBUG = true;

float deg_to_rads(float);

Player::Player() {
	this->setX(40);
	this->setY(40);
	this->setWidth(50);
	this->setHeight(50);
	this->setDirection(0);
	this->setMoveSpeed(200.f);
	this->setRotateSpeed(50.f);
	this->floating = true;
	int offset = (int)this->getWidth() / 10;
	this->setCollider(new SDL_Rect { (int)this->getX(), (int)this->getY(), (int)this->getWidth(), (int)this->getHeight() });
	this->orientors[0] = new SDL_Rect{ (int)this->getX(), (int)this->getY(), this->getWidth() - offset, offset };
	this->orientors[1] = new SDL_Rect{ (int)this->getX(), (int)this->getY(), offset, this->getWidth() - offset };
	this->orientors[2] = new SDL_Rect{ (int)this->getX(), (int)this->getY(), this->getWidth() - offset, offset };
	this->orientors[3] = new SDL_Rect{ (int)this->getX(), (int)this->getY(), offset, this->getWidth() - offset };

	this->gun = new Gun(500, 50);

	// Test purpose
	// will probably add a constructor that takes this or it gets the initial velocity from spawn point
	if(DEBUG)
		this->setVelocityY(this->getMoveSpeed());
}

Player::~Player() {
	free();
}

void Player::free() {
	pTexture.free();
}

bool Player::loadMedia(SDL_Renderer* renderer) {
	bool success = true;
	if (!pTexture.loadFromFile(renderer, "DEFNF.png", this->getWidth(), this->getHeight()))
	{
		std::cerr << "Failed to load player texture!" << std::endl;
		success = false;
	}
	return success;
}

void Player::move(double timeStep) {

	this->getCollider()->x = this->getX();
	this->getCollider()->y = this->getY();

	this->orientors[0]->x = this->getX() + 2;
	this->orientors[0]->y = this->getY() - 6;

	this->orientors[1]->x = this->getX() + this->getWidth() + 2;
	this->orientors[1]->y = this->getY() + 2;

	this->orientors[2]->x = this->getX() + 2;
	this->orientors[2]->y = this->getY() + this->getHeight() + 2;

	this->orientors[3]->x = this->getX() - 6;
	this->orientors[3]->y = this->getY() + 2;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (this->isFloating()) {
		// Rotate while floating
		if (currentKeyStates[SDL_SCANCODE_A]) {
			// Rotates Character
			this->setDirection(this->getDirection() + this->getRotateSpeed() * timeStep);
			// apply a light change in velocity
		}
		else if (currentKeyStates[SDL_SCANCODE_D]) {
			// Rotates Character
			this->setDirection(this->getDirection() - this->getRotateSpeed() * timeStep);
			// apply a light change in velocity
		}

		this->setDirection(std::fmod(this->getDirection(), 360));
	}
	else {
		// Move when attached to ground
		// left and right will be relative to the ground they are on (use getDirection with MATH)
		// upside down they will have reverse controls
		if (currentKeyStates[SDL_SCANCODE_A]) {
			this->setVelocityX(this->getMoveSpeed() * -cos(deg_to_rads(this->getDirection())));
			this->setVelocityY(this->getMoveSpeed() * -sin(deg_to_rads(this->getDirection())));
		}
		else if (currentKeyStates[SDL_SCANCODE_D]) {
			this->setVelocityX(-this->getMoveSpeed() * -cos(deg_to_rads(this->getDirection())));
			this->setVelocityY(-this->getMoveSpeed() * -sin(deg_to_rads(this->getDirection())));
		}
		else {
			this->setVelocityX(0);
			this->setVelocityY(0);
		}
		
		if (currentKeyStates[SDL_SCANCODE_SPACE]) {
			this->setVelocityX(this->getVelocityX() + (this->getMoveSpeed() * sin(deg_to_rads(this->getDirection()))));
			this->setVelocityY(this->getVelocityY() + (this->getMoveSpeed() * -cos(deg_to_rads(this->getDirection()))));
			toggleFloating();
		}
	}

	this->setX(this->getX() + (this->getVelocityX() * timeStep));
	this->setY(this->getY() + (this->getVelocityY() * timeStep));
}

void Player::render(SDL_Renderer* renderer) {

	// Draw Player Texture
	pTexture.render(renderer, this->getX(), this->getY(), NULL, this->getDirection(), NULL, SDL_FLIP_NONE);

	if (DEBUG) {
		// Draw Collider
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, this->getCollider());

		// Draw Orientors
		for (int i = 0; i < 4; i++) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawRect(renderer, this->orientors[i]);
		}
	}
}

void Player::collide(int i) {
	this->toggleFloating();
	this->setVelocityX(0);
	this->setVelocityY(0);
	this->setDirection( (i-2) * 90);
}

void Player::wrap(int w, int h) {
	if (this->getX() + this->getWidth() < 0)
		this->setX(w);
	if (this->getY() + this->getHeight() < 0)
		this->setY(h);

	if (this->getX() > w)
		this->setX(this->getX() - w - this->getWidth());
	if (this->getY() > h)
		this->setY(this->getY() - h - this->getHeight());
}

// Mutators

void Player::setWidth(int w) { this->width = w; }
void Player::setHeight(int h) { this->height = h; }

void Player::setX(float x) { this->x = x; }
void Player::setY(float y) { this->y = y; }
void Player::setVelocityX(float v) { this->velocityX = v; }
void Player::setVelocityY(float v) { this->velocityY = v; }
void Player::setDirection(float d) { this->direction = d; }
void Player::setMoveSpeed(float s) { this->moveSpeed = s; }
void Player::setRotateSpeed(float s) { this->rotateSpeed = s; }

void Player::setCollider(SDL_Rect* b) { this->collider = b; }

void Player::toggleFloating() { this->floating = !this->floating; }

// Accessors

int Player::getWidth() { return this->width; }
int Player::getHeight() { return this->height; }

float Player::getX() { return this->x; }
float Player::getY() { return this->y; }
float Player::getVelocityX() { return this->velocityX; }
float Player::getVelocityY() { return this->velocityY; }
float Player::getDirection() { return this->direction; }
float Player::getMoveSpeed() { return this->moveSpeed; }
float Player::getRotateSpeed() { return this->rotateSpeed; }

bool Player::isFloating() { return this->floating; }

SDL_Rect* Player::getCollider() { return this->collider; }

// MISC

float deg_to_rads(float input) {
	return (input * M_PI) / 180.f;
}