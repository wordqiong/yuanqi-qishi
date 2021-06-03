#include"Gun.h"

bool Gun::init() {
	if (!Entity::init()) {
		return false;
	}
	//init中写得少，限制条件反而更少，有利于创建多种类，init中应只写该类的通用属性，特化不同的对象只需在建立对象时写
	return true;
}

//这个函数参数可以传枪支的坐标，这样让子弹的初始坐标在枪支前面一点。
void Gun::createBullets(int X,int Y) {
	Bullet* bullet = Bullet::create();
	bullet->bindSprite(Sprite::create("fireBullet.png"));
	bullet->getSprite()->setPosition(Point(X+42, Y+5));//设置子弹的初始位置
	this->addChild(bullet);//显示出子弹
	this->BulletsVector.pushBack(bullet);//把创建的子弹插到自己的vector中
}


void Gun::Fire() {
	this->createBullets(this->getSprite()->getPositionX(),this->getSprite()->getPositionY());

}