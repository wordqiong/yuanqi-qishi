#pragma once
#ifndef __BOX_H__
#define __BOX_H__

#define BoxNumber 10
#define BoxBlood 5
#include "Enemy.h"
#include "MapScene.h"
#include "cocos2d.h"
class Box :public  EnemyMonster
{
public:
	virtual bool init();

	int PositionX[BoxNumber], PositionY[BoxNumber];

	void BoxInit();

	static Box* createBox();

	Box* box[BoxNumber];

	bool isFade;

	void OriginalPosition(int RoomNumber);//���ɳ�ʼλ��

	cocos2d::Sprite* _Box;//���ӵľ���ʵ�� 

	CREATE_FUNC(Box);

	cocos2d::Animate* createAnimate_box();

	void isDead();

	void DeadUpdate(float dt);

	void Fade();
};




#endif