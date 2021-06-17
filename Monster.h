#ifndef _MONSTER_H__
#define _MONSTER_H__
#include"Entity.h"


class Monster : public Entity {
public:
	
	CREATE_FUNC(Monster);
	virtual bool init();
public:
	void show();
	int blood = 15;
	/*void hide();
	void rest();
	void isAlive();*/

	bool isAlive= true;
};
#endif