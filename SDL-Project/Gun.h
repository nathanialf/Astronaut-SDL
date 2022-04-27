#pragma once
#pragma once
#include <SDL.h>chrome

class Gun {
public:

	void free();

	Gun();
	Gun(int, float);
	~Gun();

	bool fire();
	void pickup(int);
private:
	int ammo;
	
	float speed;
	float fireRate;

	void setAmmo(int);
	void setSpeed(float);
	void setFireRate(float);

	int getAmmo();
	float getSpeed();
	float getFireRate();
};