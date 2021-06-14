#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#define BossBlood1 500
#define BossBlood2 400
#define BossSpeed  10
#include "Enemy.h"
#include "MapScene.h"
#include "cocos2d.h"
class Boss :public  EnemyMonster
{
public:
	virtual bool init();

	int BossType;

	void BossInit(int BossType);

	static Boss* createBoss();

	cocos2d::Sprite*boss;//箱子的精灵实例 

	void MoveBoss();

	void BossResume();

	cocos2d::Animate* createAnimate_move(int direction, int num);

	cocos2d::Animate* createAnimate_attack(int BossType, int direction,int num);

	void isDead();

	void AttackUpdate(float dt);

	void MoveUpdate(float dt);

	int AttackTime[3];

	bool inAttack;

	CREATE_FUNC(Boss);

};




#endif#pragma once
