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
	void Fire();//����
	void createBullets(int X,int Y);//�����ӵ�����


	//�Ժ���Ϊprivate���ٸ��������ӿڵ��ͺ���

	Vector<Bullet*> BulletsVector;//���ڴ����ӵ�
	//string imgload_of_Gun;//ǹ��ͼƬ·��
	//string imagload_of_Bullet;//�ӵ���ͼƬ·��
};

#endif // !_GUN_H__

