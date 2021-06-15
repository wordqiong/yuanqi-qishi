#ifndef __HERO_H__
#define __HERO_H__

#define HeroBlood 100
#define HeroMp 180
#define HeroAc 5
#include "MapScene.h"

#include "cocos2d.h"

class Hero : public cocos2d::Sprite
{
public:

	cocos2d::Sprite* hero;

	virtual bool init();

	static Hero* createHero();

	void HeroInit();

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

	CREATE_FUNC(Hero);
protected:

};

#endif