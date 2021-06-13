#pragma once
#ifndef __BOX_H__
#define __BOX_H__

#define BoxNumber 5
#define BoxBlood 10
#include "Enemy.h"
#include "MapScene.h"
#include "cocos2d.h"
class Box :public  EnemyMonster
{
public:
	virtual bool init();

	void BoxInit();

	static Box* createBox();

	Box* box[BoxNumber];

	cocos2d::Sprite* _Box;//���ӵľ���ʵ�� 

	CREATE_FUNC(Box);

	cocos2d::Animate* createAnimate_box();

	void isDead();

	void Fade();
};




#endif