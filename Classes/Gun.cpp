#include"Gun.h"
#include "cocos2d.h"
#include"MapScene.h"

USING_NS_CC;

bool Gun::init() {
	if (!Entity::init()) {
		return false;
	}
	is_fire = false;//û����
	unsigned seed = time(0);
	srand(seed);
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::myupdate), 0.20);
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::bindMonsterupdate), 2.0);//02���һ������Ĺ����ֹǹ����
	this->schedule(CC_SCHEDULE_SELECTOR(Gun::ColdWeaponUpdate), 1.0);//�ӽ�
	return true;
}

//��������������Դ�ǹ֧�����꣬�������ӵ��ĳ�ʼ������ǹ֧ǰ��һ�㡣��ǹ�͹��������
void Gun::createBullets(Point X_Y_of_Gun, Point direction_vector) {
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
	this->createBullets(this->getSprite()->getPosition(), this->shootVector);

}

//���Ƕ���ת
void Gun::revolve(float degree) {
	/*this->getSprite()->runAction(RotateTo::create(0.5f, degree));*/
	this->getSprite()->setRotation(degree);
}
//�������
EnemyMonster* Gun::Shortest() {
	EnemyMonster* Monster;
	Map< int, EnemyMonster*> map;
	for (int i = 0; i < MonsterNumber; i++) {
		if (MapScene::sharedScene->monster->monster[i]->blood > 0) {
			Point Pt = MapScene::sharedScene->monster->monster[i]->getPosition() - this->getSprite()->getPosition();
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
	this->shootVector = monster1->Monster->getPosition() - this->getSprite()->getPosition();
	float radians = atan2(-shootVector.y, shootVector.x);
	float degree = CC_RADIANS_TO_DEGREES(radians);
	return degree;
}

void Gun::myupdate(float dt) {
	if (this->is_fire) {
		if (!this->is_coldWeapon) {
			this->Fire();
		}
	}
}

void Gun::ColdWeaponUpdate(float dt) {
	if (this->is_fire) {
		if (this->is_coldWeapon) {
			this->getSprite()->runAction(SwordAttack());


			//���ӵ�
			for (auto bullet : MapScene::sharedScene->MonsterBulletsVector) {
				if (!bullet->isNeedFade) {
					Point vector = bullet->getSprite()->getPosition() - this->getSprite()->getPosition();
					float length = vector.length();
					if (length <= this->coldWeaponLength) {
						if (MapScene::sharedScene->Hero->direction == 1 && vector.x <= 0) {
							bullet->isNeedFade = true;
							bullet->getSprite()->setVisible(false);
							Sprite* BulletBone;
							BulletBone = Sprite::create("bullet6.png");
							MapScene::sharedScene->map->addChild(BulletBone);
							BulletBone->setScale(0.5f);
							BulletBone->setPosition(Vec2(bullet->getSprite()->getPositionX(), bullet->getSprite()->getPositionY()));
							/* ����ͼƬ֡������� */
							SpriteFrameCache* frameCache_2 = SpriteFrameCache::getInstance();
							frameCache_2->addSpriteFramesWithFile("bullet.plist", "bullet.png");
							/* �ø������ߴ������� */
							animation_bullet = AnimationUtil::createAnimWithFrameNameAndNum("bullet", 6, 0.1f, 1);
							BulletBone->runAction(Animate::create(animation_bullet));
						}
						if (MapScene::sharedScene->Hero->direction == 2 && vector.x >= 0) {
							bullet->isNeedFade = true;
							bullet->getSprite()->setVisible(false);
							Sprite* BulletBone;
							BulletBone = Sprite::create("bullet6.png");
							MapScene::sharedScene->map->addChild(BulletBone);
							BulletBone->setScale(0.5f);
							BulletBone->setPosition(Vec2(bullet->getSprite()->getPositionX(), bullet->getSprite()->getPositionY()));
							/* ����ͼƬ֡������� */
							SpriteFrameCache* frameCache_2 = SpriteFrameCache::getInstance();
							frameCache_2->addSpriteFramesWithFile("bullet.plist", "bullet.png");
							/* �ø������ߴ������� */
							animation_bullet = AnimationUtil::createAnimWithFrameNameAndNum("bullet", 6, 0.1f, 1);
							BulletBone->runAction(Animate::create(animation_bullet));
						}
					}
				}
			}
			//�����
			if (MapScene::sharedScene->Hero->RoomPosition > 0 && !MapScene::sharedScene->monster->isAllDead()) {
				for (int i = 0; i < MonsterNumber; i++) {
					if (MapScene::sharedScene->monster->monster[i]->blood > 0) {
						Point vector = MapScene::sharedScene->monster->monster[i]->Monster->getPosition() - this->getSprite()->getPosition();
						float length = vector.length();
						if (length <= this->coldWeaponLength) {
							if (MapScene::sharedScene->Hero->direction == 1 && vector.x <= 0) {
								MapScene::sharedScene->monster->monster[i]->blood -= 3;
								Sprite* Blood;
								Blood = Sprite::create("bloodDelete2.png");
								Blood->setScale(1.5f);
								MapScene::sharedScene->map->addChild(Blood);
								Blood->setPosition(Vec2(MapScene::sharedScene->monster->monster[i]->Monster->getPositionX(), MapScene::sharedScene->monster->monster[i]->Monster->getPositionY() + 40));
								SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
								frameCache->addSpriteFramesWithFile("bloodDelete.plist", "bloodDelete.png");
								Animation* animation = AnimationUtil::createAnimWithFrameNameAndNum("bloodDelete", 2, 1.0f, 1);
								Blood->runAction(Animate::create(animation));

							}
							if (MapScene::sharedScene->Hero->direction == 2 && vector.x >= 0) {
								MapScene::sharedScene->monster->monster[i]->blood -= 3;
								Sprite* Blood;
								Blood = Sprite::create("bloodDelete2.png");
								Blood->setScale(1.5f);
								MapScene::sharedScene->map->addChild(Blood);
								Blood->setPosition(Vec2(MapScene::sharedScene->monster->monster[i]->Monster->getPositionX(), MapScene::sharedScene->monster->monster[i]->Monster->getPositionY() + 40));
								SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
								frameCache->addSpriteFramesWithFile("bloodDelete.plist", "bloodDelete.png");
								Animation* animation = AnimationUtil::createAnimWithFrameNameAndNum("bloodDelete", 2, 1.0f, 1);
								Blood->runAction(Animate::create(animation));

							}
						}
					}
				}
			}
		}
	}
}

//��������һ�ι���
void Gun::bindMonsterupdate(float dt) {
	if (MapScene::sharedScene->Hero->RoomPosition > 0 && (!MapScene::sharedScene->monster->isAllDead())) {
		MapScene::sharedScene->Hero->bindedMonster = this->Shortest();
	}
}
Animate* Gun::SwordAttack()
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("swordattack.plist", "swordattack.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <=10; i++)
	{
		log("picture%d", i);
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("sword%d.png",i));
		frameArray.pushBack(frame);

	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}