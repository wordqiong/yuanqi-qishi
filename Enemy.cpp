#include "Enemy.h"
#include "MapScene.h"
#include "MoveHero.h"
USING_NS_CC;




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
		addChild(monster[i]->Monster);
	}
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::MoveUpdate), 0.5);
	return true;

}

void EnemyMonster::MonsterInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MonsterType = 0;//初始化类型为0


	PositionX = rand() % 300 + 10 + origin.x;
	PositionY = rand() % 300 + 10 + origin.y;//写好OriginalPosition()函数后，改为用该函数生成初始坐标
}

void EnemyMonster::start(int type, int positionX, int positionY)
{
	this->MonsterType = type;
	if (MonsterType == 1)
	{
		Monster = Sprite::create("master.png");
		blood = 20;
		speed = 6;
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
		Monster = Sprite::create("pig.png");
		blood = 8;
		speed = 8;
		Monster->setScale(0.6f);
	}
	Monster->setPosition(PositionX, PositionY);

}

void EnemyMonster::MoveMonster()
{

	auto dr = MoveHero::sharedLayer->hero->getPosition()-Monster->getPosition();//位移向量
	auto v = dr / dr.length() * speed;//速度向量
	auto dx = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
		(rand() % (200 * speed) - 100 * speed) / 100.0);//随机偏差向量
	auto ds = v + dx;//实际位移向量
	auto moveBy = MoveBy::create(0.5, ds);
	Monster->runAction(moveBy);
}



void EnemyMonster::MoveUpdate(float dt)//移动所有小怪（测试用）
{

	for (int i = 0; i < MonsterNumber; i++)
	{
		monster[i]->MoveMonster();
	}

}

void EnemyMonster::isDead()
{
	if (blood == 0)
	{
		MonsterType = 0;
	}
}

/*bool inAttack()
{

}*/