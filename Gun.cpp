#include"Gun.h"
#include "cocos2d.h"
#include"MapScene.h"
#include <map>
#include<iostream>
using namespace std;

USING_NS_CC;

bool Gun::init() {
	if (!Entity::init()) {
		return false;
	}
	is_fire = false;//û����
	unsigned seed = time(0);
	srand(seed);
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::myupdate),0.20);//��֪��զ����
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::bindMonsterupdate), 0.5);//02���һ������Ĺ����ֹǹ����
	return true;
}

//��������������Դ�ǹ֧�����꣬�������ӵ��ĳ�ʼ������ǹ֧ǰ��һ�㡣��ǹ�͹��������
void Gun::createBullets(Point X_Y_of_Gun,Point direction_vector) {
	Bullet* bullet = Bullet::create(); 
	
	bullet->bindSprite(Sprite::create("fireBullet.png"));
	int y = (int)direction_vector.y; int x = (int)direction_vector.x; int L = x * x + y * y;
	int s = (int)sqrt((double)(L));
	
	
	float f = (float)(rand() % bullet->Bullet_accuracy + 7) / 10;
	bullet->numx = (f)*x;
	bullet->numy = y;

	bullet->getSprite()->setPosition(Vec2((float)((int)X_Y_of_Gun.x + 45 * (int)(direction_vector.x) / s), (float)(5 + (int)X_Y_of_Gun.y + 45 * (int)(direction_vector.y) / s)));//�����ӵ��ĳ�ʼλ��
	
	float radians = atan2(-direction_vector.y, direction_vector.x);//������ת���ɽǶ�
	float degree = CC_RADIANS_TO_DEGREES(radians);
	bullet->getSprite()->setRotation(degree);

	this->addChild(bullet);//��ʾ���ӵ�
	
	this->BulletsVector.pushBack(bullet);//�Ѵ������ӵ��嵽�Լ���vector��
	
}


void Gun::Fire() {
	this->createBullets(this->getSprite()->getPosition(),this->shootVector);

}

//���Ƕ���ת
void Gun::revolve(float degree) {
	/*this->getSprite()->runAction(RotateTo::create(0.1f, degree));*///ˢ�¹��죬������������
	this->getSprite()->setRotation(degree);
}
//�������
EnemyMonster* Gun::Shortest() {
	EnemyMonster* Monster;
	Map< int, EnemyMonster*> map;
	for (int i = 0; i < MonsterNumber; i++) {
		if (MapScene::sharedScene->monster->monster[i]->blood > 0) {
			Point Pt = MapScene::sharedScene->monster->monster[i]->Monster->getPosition() - this->getSprite()->getPosition();
			int f = (int)Pt.length();
			map.insert(f, MapScene::sharedScene->monster->monster[i]);
		}
	}
	Map< int, EnemyMonster*>::iterator iter = map.begin();
	Monster = iter->second;
	return Monster;
}
//���������������Ƕ�
float Gun::bindEnemy(EnemyMonster* monster1) {
	//�����������	
	this->shootVector= monster1->Monster->getPosition() - this->getSprite()->getPosition();
	float radians = atan2(-shootVector.y, shootVector.x);
	float degree = CC_RADIANS_TO_DEGREES(radians);
    return degree;
}

void Gun::myupdate(float dt) {
	if (this->is_fire) {
		this->Fire();
	}
}
//��������һ�ι���
void Gun::bindMonsterupdate(float dt) {
	if (MapScene::sharedScene->Hero->RoomPosition > 0 && (!MapScene::sharedScene->monster->isAllDead())) {
		MapScene::sharedScene->Hero->bindedMonster = this->Shortest();
	}
}