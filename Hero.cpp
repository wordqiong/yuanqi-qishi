#include "Hero.h"

void Hero::addGun(Gun* gun) {
	if (this->GunOfHero.size() == 1) {
		this->GunOfHero.push_back(gun);
	}
	if (this->GunOfHero.size() == 2) {
		this->GunOfHero.pop_back();
		this->GunOfHero.push_back(gun);
	}
	
}

bool Hero::init() {
	if (!Entity::init()) {
		return false;
	}
	

	return true;
}