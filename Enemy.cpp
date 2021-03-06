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
		x_min = 39 * 32;
		x_max = 66 * 32;
		y_min = 83 * 32;
		y_max = 96 * 32;
	}
	else if (RoomNumber == 2)
	{
		x_min = 6 * 32;
		x_max = 18 * 32;
		y_min = 45 * 32;
		y_max = 57 * 32;
	}
	else if (RoomNumber == 3)
	{
		x_min = 40 * 32;
		x_max = 66* 32;
		y_min = 41 * 32;
		y_max = 60 * 32;
	}
	else if (RoomNumber == 4)
	{
		x_min = 40 * 32;
		x_max = 68 * 32;
		y_min = 6 * 32;
		y_max = 23 * 32;
	}
	do {
		PositionX = rand() % (x_max - x_min) - 32 + x_min;
		PositionY = rand() % (y_max - y_min) - 32 + y_min;
	} 	while ((!MapScene::sharedScene->isCanReach(PositionX, PositionY, MAP_BARRIER_TREE)
		|| ((!MapScene::sharedScene->isCanReach(PositionX, PositionY)))))
		;
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
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::MoveUpdate), 0.3f);
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::AttackUpdate), 3.0f);
	schedule(CC_SCHEDULE_SELECTOR(EnemyMonster::DeadUpdate), 0.1f);
	return true;

}

void EnemyMonster::monsterInit()//对类进行初始化
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

void EnemyMonster::MonsterInit()//对精灵进行初始化
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	direction = 1;//初始状态向右
	isStand = true;//初始状态为站立
	isFade = false;
	for(int i=1;i<=3;i++)
	   inAttack[i] = false;//初始状态为不攻击
	AttackTime[1] = attack_time_of_pig;
	AttackTime[2] = attack_time_of_shooter;
	AttackTime[3] = attack_time_of_archer;//设置怪物攻击间隔
	isDirectionChange = false;//初始状态为方向不改变
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
		speed = 10;
		Monster->setScale(0.6f);
	}
	else if (MonsterType == 2)
	{
		Monster = Sprite::create("shooter.png");
		blood = 8;
		speed = 5;
		Monster->setScale(0.6f);
	}
	else if (MonsterType == 3)
	{
		Monster = Sprite::create("archer.png");
		blood = 12;
		speed = 3;
		Monster->setScale(0.6f);
	}
	Monster->setPosition(PositionX, PositionY);
	Monster->setVisible(true);
}

void EnemyMonster::MoveMonster(int num)
{
	static Point ds[MonsterNumber];
	static int k[MonsterNumber] = { 0 };
	if (k[num] == 0)
	{
		ds[num] = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
			(rand() % (200 * speed) - 100 * speed) / 100.0);
		k[num]++;
	}
	while ((!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY(), MAP_WALL))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY(), MAP_BARRIER_TREE))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY(), MAP_DOOR))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY()))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX(), Monster->getPositionY() + ds[num].y, MAP_WALL))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX(), Monster->getPositionY() + ds[num].y, MAP_BARRIER_TREE))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX(), Monster->getPositionY() + ds[num].y, MAP_DOOR))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX(), Monster->getPositionY() + ds[num].y))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY() + ds[num].y, MAP_WALL))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY() + ds[num].y, MAP_BARRIER_TREE))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY() + ds[num].y, MAP_DOOR))
		|| (!MapScene::sharedScene->isCanReach(Monster->getPositionX() + ds[num].x, Monster->getPositionY() + ds[num].y))
		)
	{

		ds[num] = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
			(rand() % (200 * speed) - 100 * speed) / 100.0);
	}
	if (ds[num].x > 0)
	{
		if (direction == 2)
		{
			direction = 1;
			isDirectionChange = true;
		}
	}
	else if (ds[num].x < 0)
	{
		if (direction == 1)
		{
			direction = 2;
			isDirectionChange = true;
		}
	}
	if ((isStand == false) && (ds[num].x == 0.0f && ds[num].y == 0.0f))
	{
		MonsterResume();
		isStand = true;
	}
	auto* animate = createAnimate_move(MonsterType, direction, 5);
	if (isDirectionChange || ((isStand) && (ds[num].x != 0.0f || ds[num].y != 0.0f)))
	{
		MonsterResume();
		isStand = false;
		Monster->runAction(animate);
	}
	auto moveBy = MoveBy::create(0.3f, ds[num]);
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

Animate* EnemyMonster::createAnimate_dead(int MonsterType, int direction, int num1,int num2,unsigned int time)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("deadmonster.plist", "deadmonster.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = num1; i <= num2; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("dead%d%d%d.png", MonsterType, direction, i));
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(time);
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
		if(!monster[i]->inAttack[monster[i]->MonsterType]&&monster[i]->blood>0)
		   monster[i]->MoveMonster(i);
	}
	

}

void EnemyMonster::isDead()
{
	Monster->stopAllActions();
	auto* animate1 = createAnimate_dead(MonsterType, direction, 1,2,1);
	auto* animate2= createAnimate_dead(MonsterType, direction, 2, 2,-1);
	Sequence* sequence = Sequence::create(animate1, animate2 , NULL);
	auto *moveBy = MoveBy::create(3.0f,Point(0.0f,-30.0f));
    Monster->runAction(sequence);
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
	static int k = 1;//记录是否处于攻击状态
	k++;
	
	for (int i = 0; i < MonsterNumber; i++)
	{
		if (monster[i]->blood > 0)
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