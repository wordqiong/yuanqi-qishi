#include "Hero.h"
void Hero::addGun(Gun* gun) {
	this->GunOfHero.push_back(gun);
}

bool Hero::init() {
	if (!Entity::init()) {
		return false;
	}

	return true;
}