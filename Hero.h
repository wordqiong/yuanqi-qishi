#ifndef __HERO_H__
#define __HERO_H__

#define HeroBlood 100

#include "MapScene.h"
#include "MapScene.h"
#include "cocos2d.h"

class Hero : public cocos2d::Sprite
{
public:

	cocos2d::Sprite* hero;

	virtual bool init();

	static Hero* createHero();

	void HeroInit();

	int blood;//人物的血量

	int direction;//获取人物移动的方向

	bool isStand;//判断人物是否站立不动

	bool isDirectionChange;//判断人物移动方向是否变化

	void update(float delta) override;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	void HeroResume();

	cocos2d::Animate* createAnimate(int direction, int num);

	CREATE_FUNC(Hero);
};

#endif