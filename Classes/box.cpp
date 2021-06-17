#include "MapScene.h"
#include "Enemy.h"
#include"box.h"
#include"Boss.h"
USING_NS_CC;

Box* Box::createBox()
{

	Box* box = new Box();

	if (box && box->init())
	{
		box->autorelease();
		box->BoxInit();
		return box;
	}
	CC_SAFE_DELETE(box);

	return NULL;
}

void Box::OriginalPosition(int RoomNumber)
{
	if (RoomNumber == 1)
	{
		for (int i = 0; i < BoxNumber / 2; i++)
		{
			PositionX[i] = 45 * 32 + i * 32;
			PositionY[i] = 90 * 32;
		}
		for (int i = BoxNumber / 2; i < BoxNumber; i++)
		{
			PositionX[i] = 45 * 32 + i * 32;
			PositionY[i] = 85 * 32;
		}
	}
	else if (RoomNumber == 2)
	{
		for (int i = 0; i < BoxNumber / 2; i++)
		{
			PositionX[i] = 10 * 32 + i * 32;
			PositionY[i] = 50 * 32;
		}
		for (int i = BoxNumber / 2; i < BoxNumber; i++)
		{
			PositionX[i] = 6 * 32 + i * 32;
			PositionY[i] = 55 * 32;
		}
	}
	else if (RoomNumber == 3)
	{
		for (int i = 0; i < BoxNumber / 2; i++)
		{
			PositionX[i] = 55 * 32 + i * 32;
			PositionY[i] = 45 * 32;
		}
		for (int i = BoxNumber / 2; i < BoxNumber; i++)
		{
			PositionX[i] = 45 * 32 + i * 32;
			PositionY[i] = 50 * 32;
		}
	}
	else if (RoomNumber == 4)
	{
		for (int i = 0; i < BoxNumber / 2; i++)
		{
			PositionX[i] = 62 * 32 + i * 32;
			PositionY[i] = 13 * 32;
		}
		for (int i = BoxNumber / 2; i < BoxNumber; i++)
		{
			PositionX[i] = 58 * 32 + i * 32;
			PositionY[i] = 10 * 32;
		}
	}
}

void Box::BoxInit()
{
	OriginalPosition(MapScene::sharedScene->Hero->RoomPosition);
	for (int i = 0; i < BoxNumber; i++)
	{
		box[i] = new Box();
		box[i]->isFade = false;
		box[i]->blood = BoxBlood;
		box[i]->_Box = Sprite::create("realbox.png");
		box[i]->_Box->setAnchorPoint(Vec2::ZERO);
		box[i]->_Box->setPosition(PositionX[i], PositionY[i]);
		box[i]->_Box->setVisible(true);
	    MapScene::sharedScene->map->addChild(box[i]->_Box,3);
	}
}

bool Box::init()
{
	if (!Layer::init())
	{
		return false;
	}

	schedule(CC_SCHEDULE_SELECTOR(Box::DeadUpdate), 0.1f);
	return true;

}

Animate* Box::createAnimate_box()
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("boxbreak.plist", "boxbreak.png");
	Vector<SpriteFrame*>frameArray;
	for (int i = 1; i <= 8; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(
			StringUtils::format("box%d.png",  i));
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);
	return Animate::create(animation);
}

void Box::isDead()
{
	auto* animate = createAnimate_box();

	


	_Box->runAction(animate);
}

void Box::DeadUpdate(float dt)
{
	for (int i = 0; i < BoxNumber; i++)
	{
		if (box[i]->blood <= 0&&box[i]->isFade==false)
		{
			box[i]->isDead();
			int mapX = (int)((PositionX[i] - 16) / 32 + 1);//地图宽从1开始
			int mapY = (int)(99 - (PositionY[i] - 16) / 32);//地图长为100
			int tileGid = MapScene::sharedScene->box_create->getTileGIDAt(Vec2(mapX, mapY));
			auto properties = MapScene::sharedScene-> map->getPropertiesForGID(tileGid);
			auto mid = properties.asValueMap().at("box");
			mid = false;
			box[i]->isFade = true;
		}
	}
}