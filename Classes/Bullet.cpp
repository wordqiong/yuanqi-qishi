#include "Bullet.h"
#include<ctime>
#include<cmath>
#include"MapScene.h"

class MapScene;

bool Bullet::init() {
	if (!Entity::init()) {
		return false;
	}

	return true;

}

//这是暂定的x方向子弹
void Bullet::MovebyLine() {

	this->S = (int)sqrt((float)(numx * numx) + (float)(numy * numy));

	this->getSprite()->setPositionX(this->getSprite()->getPositionX() + 20 * numx / S);
	this->getSprite()->setPositionY(this->getSprite()->getPositionY() + 20 * numy / S);
}

////再写个根据小怪位置定向的MovebyLine函数,传入方向参数X和Y和速度参数V,此函数暂定！！！

//void Bullet::MovebyLine(int X,int Y,int V) {
//	this->getSprite()->setPositionX(this->getSprite()->getPositionX() + (V * X / (X * X + Y * Y)));
//	this->getSprite()->setPositionY(this->getSprite()->getPositionY() + (V * Y / (X * X + Y * Y)));
//}

//子弹消失函数，诶这个应该写在Gun类里，直接将满足消失条件的子弹从BulletsVector中移除即可
void Bullet::Fade() {

}

bool Bullet::is_hit_Monster(EnemyMonster* monster) {
	Rect entityRect = monster->Monster->getBoundingBox();
	Point BulletPos = this->getSprite()->getPosition();
	return entityRect.containsPoint(BulletPos);
}



void Bullet::CreateAnimation() {
	Sprite* BulletBone;
	BulletBone = Sprite::create("bullet6.png");
	MapScene::sharedScene->map->addChild(BulletBone);
	BulletBone->setScale(0.5f);
	BulletBone->setPosition(Vec2(this->getSprite()->getPositionX(), this->getSprite()->getPositionY()));
	/* 加载图片帧到缓存池 */
	SpriteFrameCache* frameCache_2 = SpriteFrameCache::getInstance();
	frameCache_2->addSpriteFramesWithFile("bullet.plist", "bullet.png");

	/* 用辅助工具创建动画 */
	Animation* animation_bullet = AnimationUtil::createAnimWithFrameNameAndNum("bullet", 6, 0.1f, 1);

	BulletBone->runAction(Animate::create(animation_bullet));
}