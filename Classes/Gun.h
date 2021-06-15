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
	void Fire();//����
	void createBullets(Point X_Y_of_Gun, Point direction_vector);//�����ӵ�����
	void revolve(float degree);
	float bindEnemy(Monster* monster1);//����������ˣ�����ǹ��Ҫ��ת�ĽǶ�
	/*void Bullet_direction();*/
	Point shootVector;//ǹ��ֵķ�������
	bool is_be_binded = false;//�Ƿ��Ѿ���hero����
	/*string GunImageLoad = "fireGun.png";*/
	bool is_can_be_used = true;

	//�Ժ���Ϊprivate���ٸ��������ӿڵ��ͺ���
	bool is_fire;//
	Vector<Bullet*> BulletsVector;//���ڴ����ӵ�
	string imgload_of_Gun;//ǹ��ͼƬ·��
	//string imagload_of_Bullet;//�ӵ���ͼƬ·��
};

#endif // !_GUN_H__

