#include "SafeRoomMove.h"
#include "MapScene.h"
#include "BackGroundMusic.h"
USING_NS_CC;
#define MAP_WALL_SAFEROOM 1
#define MAP_BARRIER 345
#define MAP_DELIVERY 59
Scene* SafeRoomMove::createScene()
{
    return SafeRoomMove::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool SafeRoomMove::init()
{
    if (!Scene::init())
    {
        return false;
    }
    SafeMap= TMXTiledMap::create("saferoom.tmx");
    barrier = SafeMap->getLayer("layer2");
    barrier->setVisible(false);
    if (SafeMap == nullptr)
    {
        log("tile map not found");
    }
    else
    {
        SafeMap->setAnchorPoint(Vec2::ZERO);
        SafeMap->setPosition(32 * -5.0f, 32 * -5.0f);
        addChild(SafeMap);
    }
    //创建hero，将它放在地图中央
    heroInit();


    //创建状态栏
    Sprite* Board = Sprite::create("board.png");
    Board->setPosition(100, 580);
    Board->setScale(0.5f);
    addChild(Board);


  

 
    scheduleUpdate();
    return true;
}
void  SafeRoomMove::heroInit()
{
    hero = Sprite::create("hero.png");
    direction = 2;//初始朝向设置为向右
    hero->setScale(0.8f);
    isStand = true;//初始状态为站立
    isDirectionChange = false;
    SafeMap->addChild(hero);
    hero->setAnchorPoint(Vec2(0.25,0));
    hero->setPosition(32 * 22.0f+10, 32 * 16.0f);//创建hero，将它放在地图中央
}
Animate* SafeRoomMove::createAnimate(int direction, int num)
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
void SafeRoomMove::HeroResume()
{
    hero->stopAllActions();
    hero->runAction(createAnimate(this->direction, 1));
}
void SafeRoomMove::update(float delta)
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
        if (direction == 2)
        {
            isDirectionChange = true;
        }
        direction = 1;//代表向左
        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = -1.41;
            if (keys[upArrow])
            {
                FinalMove(offsetX, offsetY, 'a', 'd', 'w');
            }
            if (keys[downArrow])
            {
                FinalMove(offsetX, offsetY, 'a', 'd', 's');
            }
        }
        else
        {
            offsetX = -4;
            FinalMove(offsetX, offsetY, 'a', 'd');
        }

    }
    if (keys[rightArrow])
    {
        if (direction == 1)
        {
            isDirectionChange = true;
        }
        direction = 2;//代表向右
        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = 1.41;
            if (keys[upArrow])
            {
                FinalMove(offsetX, offsetY, 'd', 'a', 'w');
            }
            if (keys[downArrow])
            {
                FinalMove(offsetX, offsetY, 'd', 'a', 's');
            }
        }
        else
        {
            offsetX = 4;
            FinalMove(offsetX, offsetY, 'd', 'a');
        }


    }
    if (keys[upArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = 1.41;
            if (keys[rightArrow])
            {
                FinalMove(offsetX, offsetY, 'w', 's', 'd');
            }
            if (keys[leftArrow])
            {
                FinalMove(offsetX, offsetY, 'w', 's', 'a');
            }
        }
        else
        {
            offsetY = 4;
            FinalMove(offsetX, offsetY, 'w', 's');
        }


    }
    if (keys[downArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = -1.41;
            if (keys[rightArrow])
            {
                FinalMove(offsetX, offsetY, 's', 'w', 'd');
            }
            if (keys[leftArrow])
            {
                FinalMove(offsetX, offsetY, 's', 'w', 'a');
            }
        }
        else
        {
            offsetY = -4;
            FinalMove(offsetX, offsetY, 's', 'w');
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

bool SafeRoomMove::isCanReach(float x, float y, int Type_Wall,bool diliver)
{
    bool result;
    int mapX = (int)((x - 16) / 32 + 1);
    int mapY = (int)(18-(y - 16) / 32);
    if (mapX < 0 || mapX>32 || mapY < 0 || mapY>19)
    {
        return false;
    }
    int tileGid =barrier->getTileGIDAt(Vec2(mapX, mapY));
    log("e:%d\nY:%d,X:%d", tileGid, mapY, mapX);
    if (diliver) 
    {
        if (tileGid == MAP_DELIVERY)
        {

            Director::getInstance()->replaceScene(MapScene::createScene());
        }
    }
    if (tileGid == Type_Wall)
    {
        result = false;//不可移动
    }
    else
    {
        result = true;//可移动
    }
    return result;
}
void SafeRoomMove::PureMapMove(float offsetX, float offsetY)
{
    auto* animate = createAnimate(direction, 3);
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(SafeMap->getPositionX() - offsetX, SafeMap->getPositionY() - offsetY));
    if (isStand == true || isDirectionChange == true)
    {
        HeroResume();
        hero->runAction(animate);
        isStand = false;
        isDirectionChange = false;
    }
    SafeMap->runAction(moveTo);
}
void SafeRoomMove::PureHeroMove(float offsetX, float offsetY)
{
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
    hero->runAction(moveTo);
}
void SafeRoomMove::AllMove(float offsetX, float offsetY)
{
    PureMapMove(offsetX, offsetY);
    PureHeroMove(offsetX, offsetY);
}

bool SafeRoomMove::JudgeWall(float offsetX, float offsetY, char key_arrow)
{
    int i = 1;
    while (i <= 8)
    {
        if (!isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            hero->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), MAP_WALL_SAFEROOM))
        {

            /* log("i=%d", i);*/
            break;
        }
        else
            i++;

    }

    if (i <= 1)
        return true;//五格范围内有墙
    else
        return false;
}
bool SafeRoomMove::WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1)
        && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL_SAFEROOM, true))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2)
            && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL_SAFEROOM, true))))
        && isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL_SAFEROOM, true))
        return true;
    else
        return false;
}
bool SafeRoomMove::JudgeBarrier(float offsetX, float offsetY, char key_arrow)
{
    if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow) * (1 * 16) + ('a' == key_arrow) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow) * (1 * 16) + ('s' == key_arrow) * (-1 * 16), MAP_BARRIER))
    {
        return true;
    }
    else
        return false;
}
void SafeRoomMove::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{
    if (WhetherHeroMove( offsetX,  offsetY,  key_arrow_1,  key_arrow_2,  key_arrow_3))
    {
        //按两个键的情况
        if (key_arrow_3 != '-')
        {
            if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL_SAFEROOM, true))
            {
                if (JudgeBarrier(offsetX, offsetY, key_arrow_3)&& JudgeBarrier(offsetX, offsetY, key_arrow_1))
                {
                    PureHeroMove(offsetX, offsetY);
                }
            }
        }
        //一个键的情况
        else
        {
            if (JudgeBarrier(offsetX, offsetY, key_arrow_1))
            {

                PureHeroMove(offsetX, offsetY);
            }
        }
    }
    else
    {
        if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL_SAFEROOM, true))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL_SAFEROOM, true))
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        AllMove(offsetX, offsetY);
                    }
                }
            }
            else
            {
                if (JudgeBarrier(offsetX, offsetY, key_arrow_1))
                {
                    AllMove(offsetX, offsetY);
                }
            }
        }
    }
}