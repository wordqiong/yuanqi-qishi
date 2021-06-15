#include"Boss.h"
USING_NS_CC;
#define attack_time_of_Boss1 3
#define attack_time_of_Boss2 3

Boss* Boss::createBoss()
{

	Boss* boss = new Boss();

	if (boss && boss->init())
	{
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);

	return NULL;
}

void Boss::BossInit(int BossType)
{
	Boss::BossType = BossType;
	OriginalPosition(MapScene::sharedScene->Hero->RoomPosition);
	if (BossType == 1)
	{
		isStand = true; 
		isDirectionChange = false;
		blood = BossBlood1;
		boss = Sprite::create("boss1.png");
		boss->setScale(0.6f);
		speed = BossSpeed;
	}
	else if (BossType == 2)
	{
		blood = BossBlood2;
		boss = Sprite::create("boss2.png");
		boss->setScale(0.6f);
	}
	direction = 1;
	inAttack = false;
	isFade = false;
	boss->setPosition(PositionX, PositionY);
	boss->setVisible(true);
	MapScene::sharedScene->map->addChild(boss);
	AttackTime[1] = attack_time_of_Boss1;
	AttackTime[2] = attack_time_of_Boss2;
}

bool Boss::init()
{
	if (!Layer::init())
	{
		return false;
	}

	srand((unsigned)time(NULL));
	BossInit(1);
	if(BossType==1)
	    schedule(CC_SCHEDULE_SELECTOR(Boss::MoveUpdate), 0.5f);
	schedule(CC_SCHEDULE_SELECTOR(Boss::AttackUpdate), 3.0f);
	schedule(CC_SCHEDULE_SELECTOR(Boss::DeadUpdate), 0.1f);
	return true;

}

Animate* Boss::createAnimate_attack(int BossType,int direction,int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bossattack.plist", "bossattack.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("attack%d%d%d.png",BossType,direction, i));
		frameArray.pushBack(frame);
		
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.35f);
	return Animate::create(animation);
}

Animate* Boss::createAnimate_move(int direction,int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bossrun.plist", "bossrun.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("boss1%d%d.png",  direction, i));
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Boss::isDead()
{
	auto* animate = FadeOut::create(3.0f);
	boss->runAction(animate);
	CC_SAFE_DELETE(boss);
}

void Boss::MoveBoss()
{
	auto dr = MapScene::sharedScene->Hero->hero->getPosition() - boss->getPosition();//位移向量
	auto v = dr / dr.length() * speed;//速度向量
	auto dx = Vec2((rand() % (200 * speed) - 100 * speed) / 100.0,
		(rand() % (200 * speed) - 100 * speed) / 100.0);//随机偏差向量
	auto ds = v + dx;//实际位移向量
	while (!MapScene::sharedScene->isCanReach(boss->getPositionX() + ds.x, boss->getPositionY() + ds.y, MAP_WALL))
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
	auto* animate = createAnimate_move(direction, 6);
	if (isDirectionChange || ((isStand) && (ds.x != 0.0f || ds.y != 0.0f)))
	{
		BossResume();
		isStand = false;
		boss->runAction(animate);
	}
	auto moveBy = MoveBy::create(0.5, ds);
	boss->runAction(moveBy);



}

void Boss::BossResume()
{

	boss->stopAllActions();
	boss->runAction(createAnimate_attack(BossType,direction, 1));
}

void Boss::MoveUpdate(float dt)
{
	if(!inAttack)
	    MoveBoss();
}

void Boss::AttackUpdate(float dt)
{
	static int k = 1;//记录是否处于攻击状态
	k++;
	inAttack = false;
	if (k % AttackTime[BossType] == 0)//开始攻击
	{
		inAttack = true;
		BossResume();
		auto* animate1 = createAnimate_attack(BossType,direction,7);
		auto* animate2 = createAnimate_attack(BossType, direction, 1);
		log("%d", BossType);
		boss->runAction(Sequence::create(animate1, animate2,NULL));
		if (BossType == 1)
		{
			//mxy
		}
		else if(BossType==2)
		{
			//mxy
		}
	}
	
}

void Boss::DeadUpdate(float dt)
{
	if (isFade == false && blood <= 0)
	{
		isDead();
		isFade = true;
	}

}