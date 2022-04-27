#include "Barrier.h"


Barrier::Barrier() {
	this->setX(0);
	this->setY(0);
	this->setWidth(50);
	this->setHeight(10);

	this->setCollider(new SDL_Rect { this->getX(), this->getY(), this->getWidth(), this->getHeight() });
}

Barrier::Barrier(int x, int y, int w, int h) {
	this->setX(x);
	this->setY(y);
	this->setWidth(w);
	this->setHeight(h);

	this->setCollider(new SDL_Rect { this->getX(), this->getY(), this->getWidth(), this->getHeight() });
}

Barrier::~Barrier() {
	this->free();
}

void Barrier::free() {

}

void Barrier::render(SDL_Renderer* renderer) {
	// Draw Collider
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, getCollider());
}

// Accessors

int Barrier::getX() { return this->x; }
int Barrier::getY() { return this->y; }
int Barrier::getWidth() { return this->width; }
int Barrier::getHeight() { return this->height; }

SDL_Rect* Barrier::getCollider() { return this->collider; }

// Mutators

void Barrier::setX(int x) { this->x = x; }
void Barrier::setY(int y) { this->y = y; }
void Barrier::setWidth(int w) { this->width = w; }
void Barrier::setHeight(int h) { this->height = h; }

void Barrier::setCollider(SDL_Rect* b) { this->collider = b; }