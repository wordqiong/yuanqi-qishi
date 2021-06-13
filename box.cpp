#include"Box.h"
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

void Box::BoxInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PositionX = rand() % 300 + 10 + origin.x;
	PositionY = rand() % 300 + 32 * 82 + origin.y;//写好OriginalPosition()函数后，改为用该函数生成初始坐标
	blood = BoxBlood;
	_Box = Sprite::create("realbox.png");
	_Box->setScale(0.6f);
	_Box->setPosition(PositionX, PositionY);
	_Box->setVisible(true);
	
	
}

bool Box::init()
{
	if (!Layer::init())
	{
		return false;
	}

	srand((unsigned)time(NULL));

	for (int i = 0; i < BoxNumber; i++)
	{
		box[i] = new Box();
		box[i]->BoxInit();
		MapScene::sharedScene->map->addChild(box[i]->_Box);
	}
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
