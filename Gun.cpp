#include"Gun.h"

bool Gun::init() {
	if (!Entity::init()) {
		return false;
	}
	//init��д���٣����������������٣������ڴ��������࣬init��Ӧֻд�����ͨ�����ԣ��ػ���ͬ�Ķ���ֻ���ڽ�������ʱд
	return true;
}

//��������������Դ�ǹ֧�����꣬�������ӵ��ĳ�ʼ������ǹ֧ǰ��һ�㡣
void Gun::createBullets(int X,int Y) {
	Bullet* bullet = Bullet::create();
	bullet->bindSprite(Sprite::create("fireBullet.png"));
	bullet->getSprite()->setPosition(Point(X+42, Y+5));//�����ӵ��ĳ�ʼλ��
	this->addChild(bullet);//��ʾ���ӵ�
	this->BulletsVector.pushBack(bullet);//�Ѵ������ӵ��嵽�Լ���vector��
}


void Gun::Fire() {
	this->createBullets(this->getSprite()->getPositionX(),this->getSprite()->getPositionY());

}