#ifndef __HERO_H__
#define __HERO_H__

#define HeroBlood 7
#define HeroMp 180
#define HeroAc 5
#define room1_x_min  37 * 32
#define room1_x_max  68 * 32
#define room1_y_min  83 * 32
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

#include "cocos2d.h"


class Hero : public cocos2d::Sprite
{
public:
	cocos2d::Sprite* hero;

	virtual bool init();

	static Hero* createHero();

	void HeroRoomUpdate(float dt);

	void HeroInit();

	int RoomPosition;//人物处在哪个房间

	int blood;//人物的血量

	int  Mp;//人物蓝量

	int Ac;//人物护甲

	int direction;//获取人物移动的方向

	bool isStand;//判断人物是否站立不动

	bool isDirectionChange;//判断人物移动方向是否变化

	void update(float delta) override;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	void HeroResume();

	cocos2d::Animate* createAnimate(int direction, int num);

	CREATE_FUNC(Hero);

	
protected:

};

#endif