#ifndef _HERO_H__
#define _HERO_H__
#include "Entity.h"
#include "Gun.h"

class Hero :public Entity{
public:
	virtual bool init();
	void addGun(Gun* gun);//绑定正在使用的枪支
	vector<Gun*> GunOfHero;//主角的枪;每次切换枪都把当前使用的枪放在后面，以便于出容器
	int blood=6;
	int shields = 6;
	bool is_twoGun= false;
	CREATE_FUNC(Hero);
};

#endif // !_HERO_H__
