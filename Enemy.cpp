#include "Enemy.h"
#include "MapScene.h"
#include "MoveHero.h"
#include"Hero.h"
USING_NS_CC;
#define Range_of_attack_pig 20
#define attack_of_pig 5
#define attack_of_shooter 10
#define attack_of_archer 15
#define attack_time_of_pig 3
#define attack_time_of_shooter 4
#define attack_time_of_archer 5

Scene* EnemyMonster::createScene()
{
	auto scene = Scene::create();
	auto layer = EnemyMonster::create();
	scene->addChild(layer);
	return scene;
}

void EnemyMonster::OriginalPosition(int RoomNumber)
{
	int x_min, x_max, y_min, y_max;
	if (RoomNumber == 1)
	{
		x_min = 38 * 32;
		x_max = 67 * 32;
		y_min = 81 * 32;
		y_max = 98 * 32;
	}
	else if (RoomNumber == 2)
	{
		x_min = 5 * 32;
		x_max = 19 * 32;
		y_min = 44 * 32;
		y_max = 58 * 32;
	}
	else if (RoomNumber == 3)
	{
		x_min = 39 * 32;
		x_max = 68* 32;
		y_min = 40 * 32;
		y_max = 61 * 32;
	}
	else if (RoomNumber == 4)
	{
		x_min = 38 * 32;
		x_max = 69 * 32;
		y_min = 5 * 32;
		y_max = 24 * 32;
	}
	PositionX = rand() % (x_max - x_min) - 32 + x_min;
	PositionY = rand() % (y_max - y_min) - 32 + y_min;
}

EnemyMonster* EnemyMonster::createMonster()
{

	EnemyMonster* monster = new EnemyMonster();

	if (monster && monster->init())
	{
		monster->autorelease();
	    monster->monsterInit();
		return monster;
	}
	CC_SAFE_DELETE(monster);

	return NULL;
}

bool EnemyMonster::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	srand((unsigned)time(NULL));
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::MoveUpdate), 0.5);
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::AttackUpdate), 3.0f);
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::DeadUpdate), 0.1f);
	return true;

}

void EnemyMonster::monsterInit()//������г�ʼ��
{
	isAllFade = false;
	for (int i = 0; i < MonsterNumber; i++)
	{
		monster[i] = new EnemyMonster();
		monster[i]->MonsterInit();
		monster[i]->start(monster[i]->MonsterType, monster[i]->PositionX, monster[i]->PositionY);
		MapScene::sharedScene->map->addChild(monster[i]->Monster);
	}
}

void EnemyMonster::MonsterInit()//�Ծ�����г�ʼ��
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	direction = 1;//��ʼ״̬����
	isStand = true;//��ʼ״̬Ϊվ��
	isFade = false;
	for(int i=1;i<=3;i++)
	   inAttack[i] = false;//��ʼ״̬Ϊ������
	AttackTime[1] = attack_time_of_pig;
	AttackTime[2] = attack_time_of_shooter;
	AttackTime[3] = attack_time_of_archer;//���ù��﹥�����
	isDirectionChange = false;//��ʼ״̬Ϊ���򲻸ı�
	OriginalPosition(MapScene::sharedScene->Hero->RoomPosition);
	MonsterType = rand() % 3 + 1;
}

void EnemyMonster::start(int type, int positionX, int positionY)
{
	this->MonsterType = type;
	if (MonsterType == 1)
	{
		Monster = Sprite::create("pig.png");
		blood = 5;
		speed = 20;
		Monster->setScale(0.6f);
	}
	else if (MonsterType == 2)
	{
		Monster = Sprite::create("shooter.png");
		blood = 8;
		speed = 10;
		Monster->setScale(0.6f);
	}
	else if (MonsterType == 3)
	{
		Monster = Sprite::create("archer.png");
		blood = 12;
		speed = 6;
		Monster->setScale(0.6f);
	}
	Monster->setPosition(PositionX, PositionY);
	Monster->setVisible(true);
}

void EnemyMonster::MoveMonster()
{
	auto dr = MapScene::sharedScene->Hero->hero->getPosition() - Monster->getPosition();//λ������
	auto v = dr / dr.length() * speed;//�ٶ�����
	auto dx = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
		(rand() % (200 * speed) - 100 * speed) / 100.0);//���ƫ������
	auto ds = v + dx;//ʵ��λ������
	while (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds.x, Monster->getPositionY() + ds.y, MAP_WALL))
	{
		dx = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
			(rand() % (200 * speed) - 100 * speed) / 100.0);
		ds = v + dx;
	}
	if (ds.x > 0)
	{
		if (direction == 2)
		{
			direction = 1;
			isDirectionChange = true;
		}
	}
	else if (ds.x < 0)
	{
		if (direction == 1)
		{
			direction = 2;
			isDirectionChange = true;
		}
	}
	if ((isStand == false) && (ds.x == 0.0f && ds.y == 0.0f))
	{
		MonsterResume();
		isStand = true;
	}
	auto* animate = createAnimate_move(MonsterType, direction, 5);
	if (isDirectionChange || ((isStand) && (ds.x != 0.0f || ds.y != 0.0f)))
	{
		MonsterResume();
		isStand = false;
		Monster->runAction(animate);
	}
	auto moveBy = MoveBy::create(0.5, ds);
	Monster->runAction(moveBy);

	
	
}

Animate* EnemyMonster::createAnimate_move(int MonsterType, int direction, int num)
{
	auto* m_frameCache= SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("monsterrun.plist", "monsterrun.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("%d%d%d.png", MonsterType, direction, i));
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

Animate* EnemyMonster::createAnimate_dead(int MonsterType, int direction, int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("deadmonster.plist", "deadmonster.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("dead%d%d%d.png", MonsterType, direction, i));
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(2.0f);
	animation->setRestoreOriginalFrame(true);
	return Animate::create(animation);
}

void EnemyMonster::MonsterResume()
{
	
	Monster->stopAllActions();
	Monster->runAction(createAnimate_move(MonsterType, direction, 1));
}

void EnemyMonster::MoveUpdate(float dt)//�ƶ�����С��
{

	for (int i = 0; i < MonsterNumber; i++)
	{
		if(!monster[i]->inAttack[monster[i]->MonsterType])
		   monster[i]->MoveMonster();
	}
	

}

void EnemyMonster::isDead()
{
	Monster->stopAllActions();
	auto* animate = createAnimate_dead(MonsterType, direction, 2);
	auto *moveBy = MoveBy::create(3.0f,Point(0.0f,-30.0f));
    Monster->runAction(animate);
	Monster->runAction(moveBy);
}

bool EnemyMonster::isAllDead()
{
	for (int i = 0; i <MonsterNumber; i++)
	{
		if (monster[i]->blood > 0)
			return false;
	}
	return true;
}

void EnemyMonster::AllMonstersfade()
{
	for (int i = 0; i < MonsterNumber; i++)
	{
		auto* animate = FadeOut::create(2.0f);
		monster[i]->Monster->runAction(animate);
		/*CC_SAFE_DELETE(monster[i]);*/
	}
}

void EnemyMonster::AttackUpdate(float dt)
{
	static int k = 1;//��¼�Ƿ��ڹ���״̬
	k++;
	for (int i = 0; i < MonsterNumber; i++)
	{
		if (k % monster[i]->AttackTime[monster[i]->MonsterType] == 0)
			monster[i]->inAttack[monster[i]->MonsterType] = true;
		else
			monster[i]->inAttack[monster[i]->MonsterType] = false;
		if (monster[i]->inAttack[monster[i]->MonsterType] == true)
		{
			auto ds = MapScene::sharedScene->Hero->hero->getPosition() - monster[i]->getPosition();
			auto s = ds.length();
			monster[i]->MonsterResume();
			/*if (monster[i]->MonsterType == 1)
			{
				if (Range_of_attack_pig >= s)
				{
					MapScene::sharedScene->heroblood = MapScene::sharedScene->heroblood - attack_of_pig;
				}
			}
			else if (MonsterType == 2)
			{

			}

			else
			{

			}*/
		}
	}
	
}

void EnemyMonster::DeadUpdate(float dt)
{
	for (int i = 0; i < MonsterNumber; i++)
	{
		if (monster[i]->blood <= 0 && monster[i]->isFade == false)
		{
			monster[i]->isDead();
			monster[i]->isFade = true;
		}
	}
	if (isAllDead()&&(!isAllFade))
		AllMonstersfade();
}