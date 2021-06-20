#ifndef _GUN_H__
#define _GUN_H__

#include"Entity.h"
#include"Bullet.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class EnemyMonster;
class Bullet;
class Gun :public Entity {
public:

	CREATE_FUNC(Gun);
	virtual bool init();
	void myupdate(float dt);

public:
	Animation* animation_bullet;
	void Fire();//开火
	void createBullets(Point X_Y_of_Gun, Point direction_vector);//创建子弹对象
	void revolve(float degree);
	float bindEnemy(EnemyMonster* monster1);//锁定最近敌人，返回枪需要旋转的角度
	/*void Bullet_direction();*/
	Point shootVector;//枪离怪的方向向量
	bool is_be_binded = false;//是否已经被hero绑定了
	/*string GunImageLoad = "fireGun.png";*/
	bool is_can_be_used = true;
	bool is_can_be_count = true;
	EnemyMonster* Shortest();
	//稍后设为private，再给个函数接口调就好啦
	bool is_fire;//
	bool is_canister = false;//是否为霰弹枪
	int canisterBulletsNum = 5;
	bool is_coldWeapon1 = false;//是否近战武器1
	bool is_coldWeapon2 = false;//是否近战武器2
	float coldWeaponLength = 30;//剑长
	Vector<Bullet*> BulletsVector;//用于储存子弹
	string imgload_of_Gun;//枪的图片路径
	void bindMonsterupdate(float dt);
	void ColdWeaponUpdate(float dt);
	//string imagload_of_Bullet;//子弹的图片路径
};

#endif // !_GUN_H__

