#include "Bullet.h"
#include<ctime>
#include<cmath>

bool Bullet::init() {
	if (!Entity::init()) {
		return false;
	}

	return true;
	
}

//�����ݶ���x�����ӵ�
void Bullet::MovebyLine() {
	
	this->S = (int)sqrt((float)(numx * numx) + (float)(numy * numy));
	
	this->getSprite()->setPositionX(this->getSprite()->getPositionX() + 20 * numx / S);
	this->getSprite()->setPositionY(this->getSprite()->getPositionY() + 20 * numy / S);
}
	
////��д������С��λ�ö����MovebyLine����,���뷽�����X��Y���ٶȲ���V,�˺����ݶ�������

//void Bullet::MovebyLine(int X,int Y,int V) {
//	this->getSprite()->setPositionX(this->getSprite()->getPositionX() + (V * X / (X * X + Y * Y)));
//	this->getSprite()->setPositionY(this->getSprite()->getPositionY() + (V * Y / (X * X + Y * Y)));
//}

//�ӵ���ʧ�����������Ӧ��д��Gun���ֱ�ӽ�������ʧ�������ӵ���BulletsVector���Ƴ�����
void Bullet::Fade() {

}