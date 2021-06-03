#ifndef _GUN_H__
#define _GUN_H__

#include"Entity.h"
#include"Bullet.h"
#include <iostream>
#include <string>
using namespace std;

class Gun :public Entity {
public:

	CREATE_FUNC(Gun);
	virtual bool init();
	

public:
	void Fire();//开火
	void createBullets(int X,int Y);//创建子弹对象


	//稍后设为private，再给个函数接口调就好啦

	Vector<Bullet*> BulletsVector;//用于储存子弹
	//string imgload_of_Gun;//枪的图片路径
	//string imagload_of_Bullet;//子弹的图片路径
};

#endif // !_GUN_H__

