#include "MapScene.h"
#include "Enemy.h"
#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_ROOM 11853
USING_NS_CC;

MapScene* MapScene::sharedScene = nullptr;
Scene* MapScene::createScene()
{
    return MapScene::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //�������������ڴ�����
    sharedScene = this;
    map = TMXTiledMap::create("map.tmx");
    layer2 = map->getLayer("layer2");
    layer2->setVisible(false);
    if (map == nullptr)
    {
        log("tile map not found");
    }
    else
    {
        map->setAnchorPoint(Vec2::ZERO);
        map->setPosition(0, -32 * (100 - 18));
        addChild(map);
    }
    heroInit();
    auto monster = EnemyMonster::createMonster();
    addChild(monster);
    scheduleUpdate();
    return true;
}

void  MapScene::heroInit()
{
    hero = Sprite::create("hero.png");
    direction = 2;//��ʼ��������Ϊ����
    isStand = true;//��ʼ״̬Ϊվ��
    isDirectionChange=false;
    map->addChild(hero);
    hero->setAnchorPoint(Vec2::ZERO);
    hero->setPosition(32 * 10.0f, 32 * 92.0f);//����hero���������ڵ�ͼ����
}

Animate* MapScene::createAnimate(int direction, int num)
{
    auto* m_frameCache = SpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("herorun.plist", "herorun.png");
    Vector<SpriteFrame*>frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = m_frameCache->getSpriteFrameByName(
           StringUtils::format( "%d%d.png", direction, i));
        frameArray.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);
    return Animate::create(animation);
}

void MapScene ::HeroResume()
{
    hero->stopAllActions();
    hero->runAction(createAnimate(this->direction, 1));
}

void MapScene::update(float delta)
{
    Node::update(delta);
    auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D,
        upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = true;
        log("%d", keyCode);
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = false;

    };
    int offsetX = 0, offsetY = 0;
    if (keys[leftArrow])
    {
        offsetX = -4;
        if (direction == 2)
        {
            isDirectionChange = true;
        }
        direction = 1;//��������
        FinalMove(offsetX, offsetY, 'a', 'd');
    }
    if (keys[rightArrow])
    {
        offsetX = 4;
        if (direction == 1)
        {
            isDirectionChange = true;
        }
        direction = 2;//��������
        FinalMove(offsetX, offsetY, 'd', 'a');

    }
    if (keys[upArrow])
    {
        offsetY = 4;
        FinalMove(0, offsetY, 'w', 's');

    }
    if (keys[downArrow])
    {
        offsetY = -4;
        FinalMove(0, offsetY, 's', 'w');
    }
    if (offsetX == 0 && offsetY == 0)
    {
        HeroResume();
        isStand = true;
    }
    offsetX = offsetY = 0;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
bool MapScene::isCanReach(float x, float y, int Type_Wall)
{
    bool result;
    int mapX = (int)((x - 16) / 32 + 1);
    int mapY = (int)(99 - (y - 16) / 32);
    if (mapX < 0 || mapX>73 || mapY < 0 || mapY>99)
    {
        return false;
    }
    int tileGid = layer2->getTileGIDAt(Vec2(mapX, mapY));
    log("e:%d\nY:%d,X:%d", tileGid, mapY, mapX);
    if (tileGid == Type_Wall)
    {
        result = false;//�����ƶ�
    }
    else
    {
        result = true;//���ƶ�
    }
    return result;
}

void MapScene::PureMapMove(int offsetX, int offsetY)
{
    auto* animate = createAnimate(direction, 3);
    auto *moveTo = MoveTo::create(1.0 / 1000, Vec2(map->getPositionX() - offsetX, map->getPositionY() - offsetY));
   if (isStand == true || isDirectionChange == true)
    {
        HeroResume();
        hero->runAction(animate);
        isStand = false;
        isDirectionChange = false;
    }
    map->runAction(moveTo);
}
void MapScene::PureHeroMove(int offsetX, int offsetY)
{
    auto* animate = createAnimate(direction, 3);
    auto *moveTo = MoveTo::create(1.0 / 1000, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
    
    if (isStand == true||isDirectionChange==true)
    {
        HeroResume();
        hero->runAction(animate);
        isStand = false;
        isDirectionChange = false;
    }
    hero->runAction(moveTo);
    
}
void MapScene::AllMove(int offsetX, int offsetY)
{
    PureMapMove(offsetX, offsetY);
    PureHeroMove(offsetX, offsetY);
}

bool MapScene::JudgeWall(int offsetX, int offsetY, char key_arrow)
{
    int i = 1;
    while (i <= 8)
    {
        if (!isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            hero->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), MAP_WALL))
        {

            log("i=%d", i);
            break;
        }
        else
            i++;

    }

    if (i <= 5)
        return true;//���Χ����ǽ
    else
        return false;
}
void MapScene::FinalMove(int offsetX, int offsetY, char key_arrow_1, char key_arrow_2)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1)
        && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2)
            && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL))))
        && isCanReach(hero->getPositionX() + offsetX+ ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1*16), hero->getPositionY() + offsetY+ ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
    {
        PureHeroMove(offsetX, offsetY);
    }
    else
    {
        if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
        {
            AllMove(offsetX, offsetY);
        }
    }
}
//void MapScene::OpenDoor()
//{
//    if (StateDoor())
//    {
//        //�������ӵ��Ǽ�������ǽ��
//    }
//
//}
//void MapScene::CloseDoor()
//{
//    if (!StateDoor())
//    {
//        //������·������ǽ��
//    }
//}
//bool MapScene::StateDoor()
//{
//    //�ƻ�Ŀ�� ��ȥ��ǰ
//    //true ���� ��������� ����
//    //false �������߽�����
//    if (PositionDoor)
//    {
//        if (!isCanReach(32 * (10 - x), 32 * (92 - y), MAP_LOBBY))
//        {
//            PositionDoor = false;
//            return true;
//        }
//    }
//    else
//    {
//        if (!isCanReach(32 * (10 - x), 32 * (92 - y), MAP_ROOM))
//        {
//            PositionDoor = true;
//            return false;
//        }
//    }
//}