#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#define HeroBlood 7
#define HeroAc 5
#define HeroMp 200
#define room1_x_min  35 * 32
#define room1_x_max  68 * 32
#define room1_y_min  79 * 32
#define room1_y_max  99 * 32
#define room2_x_min  4 * 32
#define room2_x_max  20 * 32
#define room2_y_min  43 * 32
#define room2_y_max  59 * 32
#define room3_x_min  38 * 32
#define room3_x_max  69* 32
#define room3_y_min  39 * 32
#define room3_y_max  62 * 32
#define room4_x_min   37 * 32
#define room4_x_max  70 * 32
#define room4_y_min  4 * 32
#define room4_y_max  25 * 32
#include "MapScene.h"
#include "MapScene.h"
#include "cocos2d.h"
#include"gun.h"

class Hero : public cocos2d::Sprite
{
public:
	EnemyMonster* bindedMonster;
	cocos2d::Sprite* hero;

	virtual bool init();

	static Hero* createHero();

	void HeroInit();

	int RoomPosition;//���ﴦ���ĸ�����

	void HeroRoomUpdate(float dt);

	void AcUpdate(float dt);

	int blood;//�����Ѫ��

	int  Mp;//��������

	int Ac;//���ﻤ��




	int direction;//��ȡ�����ƶ��ķ���

	bool isStand;//�ж������Ƿ�վ������

	bool isDirectionChange;//�ж������ƶ������Ƿ�仯

	void update(float delta) override;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	void HeroResume();

	cocos2d::Animate* createAnimate(int direction, int num);

	void addGun(Gun* gun);//������ʹ�õ�ǹ֧
	vector<Gun*> GunOfHero;//���ǵ�ǹ;ÿ���л�ǹ���ѵ�ǰʹ�õ�ǹ���ں��棬�Ա��ڳ�����
	bool is_twoGun = false;

	CREATE_FUNC(Hero);
};

#endif