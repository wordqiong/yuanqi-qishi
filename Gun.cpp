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
	is_fire = false;//没开火
	unsigned seed = time(0);
	srand(seed);
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::myupdate),0.20);//不知道咋回事
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::bindMonsterupdate), 0.5);//02秒绑定一次最近的怪物，防止枪抖动
	return true;
}

//这个函数参数可以传枪支的坐标，这样让子弹的初始坐标在枪支前面一点。传枪和怪物的向量
void Gun::createBullets(Point X_Y_of_Gun,Point direction_vector) {
	Bullet* bullet = Bullet::create(); 
	
	bullet->bindSprite(Sprite::create("fireBullet.png"));
	int y = (int)direction_vector.y; int x = (int)direction_vector.x; int L = x * x + y * y;
	int s = (int)sqrt((double)(L));
	
	
	float f = (float)(rand() % bullet->Bullet_accuracy + 7) / 10;
	bullet->numx = (f)*x;
	bullet->numy = y;

	bullet->getSprite()->setPosition(Vec2((float)((int)X_Y_of_Gun.x + 45 * (int)(direction_vector.x) / s), (float)(5 + (int)X_Y_of_Gun.y + 45 * (int)(direction_vector.y) / s)));//设置子弹的初始位置
	
	float radians = atan2(-direction_vector.y, direction_vector.x);//将弧度转换成角度
	float degree = CC_RADIANS_TO_DEGREES(radians);
	bullet->getSprite()->setRotation(degree);

	this->addChild(bullet);//显示出子弹
	
	this->BulletsVector.pushBack(bullet);//把创建的子弹插到自己的vector中
	
}


void Gun::Fire() {
	this->createBullets(this->getSprite()->getPosition(),this->shootVector);

}

//传角度旋转
void Gun::revolve(float degree) {
	/*this->getSprite()->runAction(RotateTo::create(0.1f, degree));*///刷新过快，来不及做动作
	this->getSprite()->setRotation(degree);
}
//求最近怪
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
//锁定最近敌人算出角度
float Gun::bindEnemy(EnemyMonster* monster1) {
	//射击方向向量	
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
//几秒锁定一次怪物
void Gun::bindMonsterupdate(float dt) {
	if (MapScene::sharedScene->Hero->RoomPosition > 0 && (!MapScene::sharedScene->monster->isAllDead())) {
		MapScene::sharedScene->Hero->bindedMonster = this->Shortest();
	}
}