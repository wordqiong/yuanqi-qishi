#include "Enemy.h"
#include "MapScene.h"
#include "MoveHero.h"
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

EnemyMonster* EnemyMonster::createMonster()
{

	EnemyMonster* monster = new EnemyMonster();

	if (monster && monster->init())
	{
		monster->autorelease();
		monster->MonsterInit();
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

	for (int i = 0; i < MonsterNumber; i++)
	{
		monster[i] = new EnemyMonster();
		monster[i]->MonsterInit();
		monster[i]->MonsterType = rand() % 3 + 1;
		monster[i]->start(monster[i]->MonsterType, monster[i]->PositionX, monster[i]->PositionY);
		MapScene::sharedScene->map->addChild(monster[i]->Monster);
	}
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::MoveUpdate), 0.5);
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::AttackUpdate), 3.0f);
	return true;

}

void EnemyMonster::MonsterInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MonsterType = 0;//初始化类型为0
	direction = 1;//初始状态向右
	isStand = true;//初始状态为站立
	for(int i=1;i<=3;i++)
	   inAttack[i] = false;//初始状态为不攻击
	AttackTime[1] = attack_time_of_pig;
	AttackTime[2] = attack_time_of_shooter;
	AttackTime[3] = attack_time_of_archer;//设置怪物攻击间隔
	isDirectionChange = false;//初始状态为方向不改变
	PositionX = rand() % 300 + 10 + origin.x;
	PositionY = rand() % 300 + 32*82 + origin.y;//写好OriginalPosition()函数后，改为用该函数生成初始坐标
	
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
	auto dr = MapScene::sharedScene->hero->getPosition() - Monster->getPosition();//位移向量
	auto v = dr / dr.length() * speed;//速度向量
	auto dx = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
		(rand() % (200 * speed) - 100 * speed) / 100.0);//随机偏差向量
	auto ds = v + dx;//实际位移向量
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

void EnemyMonster::MoveUpdate(float dt)//移动所有小怪
{

	for (int i = 0; i < MonsterNumber; i++)
	{
		if (!monster[i]->inAttack[monster[i]->MonsterType])
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
		if (monster[i]->blood != 0)
			return false;
	}
	return true;
}

void EnemyMonster::AllMonstersfade()
{
	for (int i = 0; i < MonsterNumber; i++)
	{
		Monster->setVisible(false);
	}
}

void EnemyMonster::AttackUpdate(float dt)
{
	static int k = 1;//记录是否处于攻击状态
	k++;
	for (int i = 0; i < MonsterNumber; i++)
	{
		if (k % monster[i]->AttackTime[monster[i]->MonsterType] == 0)
			monster[i]->inAttack[monster[i]->MonsterType] = true;
		else
			monster[i]->inAttack[monster[i]->MonsterType] = false;
		if (monster[i]->inAttack[monster[i]->MonsterType] == true)
		{
			auto ds = MapScene::sharedScene->hero->getPosition() - monster[i]->getPosition();
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