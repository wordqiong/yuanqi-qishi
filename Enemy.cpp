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
		MapScene::sharedScene->map->addChild(monster[i]->Monster);
	}
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::MoveUpdate), 0.5);
	return true;

}

void EnemyMonster::MonsterInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MonsterType = 0;//初始化类型为0
	direction = 1;//初始状态向右
	isStand = true;//初始状态为站立
	isDirectionChange = false;
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
	if ((isStand==false)&&(ds.x==0.0f&&ds.y==0.0f))
	{
		MonsterResume();
		isStand = true;
	}
	auto* animate = createAnimate(MonsterType,direction,  5);
	if (isDirectionChange||((isStand)&& (ds.x!= 0.0f || ds.y != 0.0f)))
	{
		MonsterResume();
		isStand = false;
		Monster->runAction(animate);
	}
	auto moveBy = MoveBy::create(0.5, ds);
	Monster->runAction(moveBy);
}

Animate* EnemyMonster::createAnimate(int MonsterType, int direction, int num)
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

void EnemyMonster::MonsterResume()
{
	Monster->stopAllActions();
	Monster->runAction(createAnimate(MonsterType, direction, 1));
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