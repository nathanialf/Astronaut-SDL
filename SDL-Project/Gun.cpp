#include "Gun.h"

Gun::Gun() {

}

Gun::Gun(int ammo, float speed) {

}

Gun::~Gun() {

}

void Gun::free() {

}

bool Gun::fire() {
	if (!this->getAmmo()) return this->getAmmo();
	this->setAmmo(this->getAmmo() - 1);
}

void Gun::pickup(int ammo) {
	this->setAmmo(this->getAmmo() + ammo);
}

void Gun::setAmmo(int ammo) { this->ammo = ammo; }
void Gun::setSpeed(float speed) { this->speed = speed; }
void Gun::setFireRate(float fr) { this->fireRate = fr; }

int Gun::getAmmo() { return this->ammo; }
float Gun::getSpeed() { return this->speed; }
float Gun::getFireRate() { return this->fireRate; }