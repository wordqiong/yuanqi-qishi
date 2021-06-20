#include"Hero.h"
USING_NS_CC;
bool Hero::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    schedule(CC_SCHEDULE_SELECTOR(Hero::update));
    schedule(CC_SCHEDULE_SELECTOR(Hero::HeroRoomUpdate));
    schedule(CC_SCHEDULE_SELECTOR(Hero::AcUpdate),3.0f);
    return true;

}

void Hero::addGun(Gun* gun) {
    if (this->GunOfHero.size() == 1) {
        this->GunOfHero.push_back(gun);
    }
    if (this->GunOfHero.size() == 2) {
        this->GunOfHero.pop_back();
        this->GunOfHero.push_back(gun);
    }

}
Hero* Hero::createHero()
{
    Hero* hero = new Hero();

    if (hero && hero->init())
    {
        hero->autorelease();
        hero->HeroInit();
        return hero;
    }
    CC_SAFE_DELETE(hero);

    return NULL;
}

void Hero::HeroInit()
{
    hero = Sprite::create("hero.png");
    direction = 2;//��ʼ��������Ϊ����
    isStand = true;//��ʼ״̬Ϊվ��
    isDirectionChange = false;
    MapScene::sharedScene->map->addChild(hero);
    hero->setAnchorPoint(Vec2::ZERO);
    hero->setScale(0.6f);
    hero->setPosition(32 * 10.0f, 32 * 92.0f);//����hero���������ڵ�ͼ����
    blood = HeroBlood;
    Ac = HeroAc;
    Mp = HeroMp;


}

Animate* Hero::createAnimate(int direction, int num)
{
    auto* m_frameCache = SpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("herorun.plist", "herorun.png");
    Vector<SpriteFrame*>frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = m_frameCache->getSpriteFrameByName(
            StringUtils::format("%d%d.png", direction, i));
        frameArray.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);
    return Animate::create(animation);
}

void Hero::HeroResume()
{
    hero->stopAllActions();
    hero->runAction(createAnimate(this->direction, 1));
}

void Hero::update(float delta)
{
   
    Node::update(delta);
    auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D,
        upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = true;
        /* log("%d", keyCode);*/
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = false;

    };
    float offsetX = 0, offsetY = 0;
    if (keys[leftArrow])
    {
        if (this->RoomPosition == 0 || MapScene::sharedScene->monster->isAllDead())
        {
            if (direction == 2)
            {
                isDirectionChange = true;
            }
            direction = 1;//��������
        }
        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = -1.41;
            if (keys[upArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'a', 'd', 'w');
            }
            if (keys[downArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'a', 'd', 's');
            }
        }
        else
        {
            offsetX = -4;
            MapScene::sharedScene->FinalMove(offsetX, offsetY, 'a', 'd');
        }

    }
    if (keys[rightArrow])
    {
        if (this->RoomPosition == 0 || MapScene::sharedScene->monster->isAllDead()) {
            if (direction == 1)
            {
                isDirectionChange = true;
            }
            direction = 2;//��������
        }

        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = 1.41;
            if (keys[upArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'd', 'a', 'w');
            }
            if (keys[downArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'd', 'a', 's');
            }
        }
        else
        {
            offsetX = 4;
            MapScene::sharedScene->FinalMove(offsetX, offsetY, 'd', 'a');
        }


    }
    if (keys[upArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = 1.41;
            if (keys[rightArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'w', 's', 'd');
            }
            if (keys[leftArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 'w', 's', 'a');
            }
        }
        else
        {
            offsetY = 4;
            MapScene::sharedScene->FinalMove(offsetX, offsetY, 'w', 's');
        }


    }
    if (keys[downArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = -1.41;
            if (keys[rightArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 's', 'w', 'd');
            }
            if (keys[leftArrow])
            {
                MapScene::sharedScene->FinalMove(offsetX, offsetY, 's', 'w', 'a');
            }
        }
        else
        {
            offsetY = -4;
            MapScene::sharedScene->FinalMove(offsetX, offsetY, 's', 'w');
        }

    }
    if (offsetX == 0 && offsetY == 0)
    {
        HeroResume();
        isStand = true;
    }
    offsetX = offsetY = 0;


    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void Hero::HeroRoomUpdate(float dt)
{
    if ((hero->getPositionX() >= room1_x_min) && (hero->getPositionX() <= room1_x_max)
        && (hero->getPositionY() >= room1_y_min) && (hero->getPositionY() <= room1_y_max))
        RoomPosition = 1;
    else if ((hero->getPositionX() >= room2_x_min) && (hero->getPositionX() <= room2_x_max)
        && (hero->getPositionY() >= room2_y_min) && (hero->getPositionY() <= room2_y_max))
        RoomPosition = 2;
    else if ((hero->getPositionX() >= room3_x_min) && (hero->getPositionX() <= room3_x_max)
        && (hero->getPositionY() >= room3_y_min) && (hero->getPositionY() <= room3_y_max))
        RoomPosition = 3;
    else if ((hero->getPositionX() >= room4_x_min) && (hero->getPositionX() <= room4_x_max)
        && (hero->getPositionY() >= room4_y_min) && (hero->getPositionY() <= room4_y_max))
        RoomPosition = 4;
    else
        RoomPosition = 0;
}

void Hero::AcUpdate(float dt)
{
    Ac++;
    
    if (Ac > HeroAc)
        Ac = HeroAc;
    MapScene::sharedScene->Boardupdate();
}

void Hero::deleteblood(int attack)
{
    if (attack <= Ac)
        Ac = Ac - attack;
    else
    {
        Ac = 0;
        blood = blood - (attack - Ac);
    }

}