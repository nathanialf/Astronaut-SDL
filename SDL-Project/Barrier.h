#pragma once
#include <SDL.h>
#include "LTexture.h"

class Barrier {
public:
	SDL_Rect* getCollider();
	
	void free();
	void render(SDL_Renderer*);

	Barrier();
	Barrier(int, int, int, int);
	~Barrier();
private:

	int x;
	int y;
	int width;
	int height;
	SDL_Rect* collider;

	LTexture bTexture;

	// Accessors

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// Mutators

	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);

	void setCollider(SDL_Rect*);
};