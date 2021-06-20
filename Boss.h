#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#define BossBlood1 500
#define BossBlood2 400
#define BossSpeed  10
#include "Enemy.h"
#include "MapScene.h"
#include "cocos2d.h"

class EnemyMonster;
class Boss :public  EnemyMonster
{
public:
	virtual bool init();

	int BossType;

	void BossInit(int BossType);

	static Boss* createBoss();



	void MoveBoss();

	void BossResume();

	cocos2d::Animate* createAnimate_move(int direction, int num);

	cocos2d::Animate* createAnimate_attack(int BossType, int direction,int num);

	void isDead();


	bool isFade;

	void DeadUpdate(float dt);

	void AttackUpdate(float dt);

	void MoveUpdate(float dt);

	void Level2_1AttackUpdate(float dt);//技能一
	void Level2_2AttackUpdate(float dt);//技能二

	Point BossShootVector;
	Vector<Bullet*> BulletsVector;

	void BossCreateBullets1(Point X_Y_of_Boss, Point direction_vector);
	void BossCreateBullets2(Point X_Y_of_Boss);

	int AttackTime[3];

	bool inAttack;

	CREATE_FUNC(Boss);

};




#endif#pragma once
