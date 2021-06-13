#ifndef _GUN_H__
#define _GUN_H__

#include"Entity.h"
#include"Bullet.h"
#include <iostream>
#include <string>
#include"Monster.h"
#include <cmath>
using namespace std;

class Gun :public Entity {
public:

	CREATE_FUNC(Gun);
	virtual bool init();
	void myupdate(float dt);

public:
	void Fire();//开火
	void createBullets(Point X_Y_of_Gun, Point direction_vector);//创建子弹对象
	void revolve(float degree);
	float bindEnemy(Monster* monster1);//锁定最近敌人，返回枪需要旋转的角度
	/*void Bullet_direction();*/
	Point shootVector;//枪离怪的方向向量


	//稍后设为private，再给个函数接口调就好啦
	bool is_fire;//
	Vector<Bullet*> BulletsVector;//用于储存子弹
	string imgload_of_Gun;//枪的图片路径
	//string imagload_of_Bullet;//子弹的图片路径
};

#endif // !_GUN_H__
