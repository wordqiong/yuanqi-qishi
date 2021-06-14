#include "MapScene.h"
#include "Enemy.h"
#include"box.h"
#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_ROOM 11853
#define HERO_BLOOD 100
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
    if (!Scene::init())
    {
        return false;
    }
    //将出生点设置在窗口下
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
    //创建hero，将它放在地图中央
    Hero=Hero::createHero() ;
    addChild(Hero);
    auto monster = EnemyMonster::createMonster();
    addChild(monster);
    auto box = Box::createBox();
    addChild(box);
    return true;
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
        result = false;//不可移动
    }
    else
    {
        result = true;//可移动
    }
    return result;
}

void MapScene::PureMapMove(float offsetX, float offsetY)
{
    auto* animate = Hero->createAnimate(Hero->direction, 3);
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(map->getPositionX() - offsetX, map->getPositionY() - offsetY));
    if (Hero->isStand == true || Hero->isDirectionChange == true)
    {
        Hero->HeroResume();
        Hero->hero->runAction(animate);
        Hero->isStand = false;
        Hero->isDirectionChange = false;
    }
    map->runAction(moveTo);
}

void MapScene::PureHeroMove(float offsetX, float offsetY)
{
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(Hero->hero->getPositionX() + offsetX, Hero->hero->getPositionY() + offsetY));
    Hero->hero->runAction(moveTo);
}

void MapScene::AllMove(float offsetX, float offsetY)
{
    PureMapMove(offsetX, offsetY);
    PureHeroMove(offsetX, offsetY);
}

bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow)
{
    int i = 1;
    while (i <= 8)
    {
        if (!isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            Hero->hero->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), MAP_WALL))
        {

            /* log("i=%d", i);*/
            break;
        }
        else
            i++;

    }

    if (i <= 2)
        return true;//五格范围内有墙
    else
        return false;
}

void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1)
        && isCanReach(Hero->hero->getPositionX() + offsetX, Hero->hero->getPositionY() + offsetY, MAP_WALL))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2)
            && isCanReach(Hero->hero->getPositionX() + offsetX, Hero->hero->getPositionY() + offsetY, MAP_WALL))))
        && isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
    {
        if (key_arrow_3 != '-')
        {
            if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
            {
                PureHeroMove(offsetX, offsetY);
            }
        }
        else
        {
            PureHeroMove(offsetX, offsetY);
        }
    }
    else
    {
        if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
                {
                    AllMove(offsetX, offsetY);
                }
            }
            else
            {
                AllMove(offsetX, offsetY);
            }
        }
    }
}
//void MapScene::OpenDoor()
//{
//    if (StateDoor())
//    {
//        //消除添加的那几个精灵墙块
//    }
//
//}
//void MapScene::CloseDoor()
//{
//    if (!StateDoor())
//    {
//        //在来的路上添加墙体
//    }
//}
//bool MapScene::StateDoor()
//{
//    //计划目标 读去当前
//    //true 则开门 代表打完怪 开门
//    //false 从走廊走进房间
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