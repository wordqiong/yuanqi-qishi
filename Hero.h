#ifndef _HERO_H__
#define _HERO_H__
#include "Entity.h"
#include "Gun.h"

class Hero :public Entity{
public:
	virtual bool init();
	void addGun(Gun* gun);//������ʹ�õ�ǹ֧
	vector<Gun*> GunOfHero;//���ǵ�ǹ;ÿ���л�ǹ���ѵ�ǰʹ�õ�ǹ���ں��棬�Ա��ڳ�����
	int blood=6;
	int shields = 6;
	bool is_twoGun= false;
	CREATE_FUNC(Hero);
};

#endif // !_HERO_H__
