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
	void Fire();//����
	void createBullets(Point X_Y_of_Gun, Point direction_vector);//�����ӵ�����
	void revolve(float degree);
	float bindEnemy(EnemyMonster* monster1);//����������ˣ�����ǹ��Ҫ��ת�ĽǶ�
	/*void Bullet_direction();*/
	Point shootVector;//ǹ��ֵķ�������
	bool is_be_binded = false;//�Ƿ��Ѿ���hero����
	/*string GunImageLoad = "fireGun.png";*/
	bool is_can_be_used = true;
	EnemyMonster* Shortest();
	//�Ժ���Ϊprivate���ٸ��������ӿڵ��ͺ���
	bool is_fire;//
	bool is_coldWeapon = false;//�Ƿ��ս����
	float coldWeaponLength = 30;//����
	Vector<Bullet*> BulletsVector;//���ڴ����ӵ�
	string imgload_of_Gun;//ǹ��ͼƬ·��
	void bindMonsterupdate(float dt);
	void ColdWeaponUpdate(float dt);
	//string imagload_of_Bullet;//�ӵ���ͼƬ·��
	Animate* SwordAttack();//���Ļӿ�����
	Animate* AxeAttack();//���ӵĻӿ�����
};

#endif // !_GUN_H__