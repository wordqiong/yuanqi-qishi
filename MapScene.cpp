#include "MapScene.h"
#include "ui/CocosGUI.h"
#include "AnimationUtil.h"
#include "BackGroundMusic.h"
#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_BARRIER_TREE 1456
#define MAP_ROOM_1 11652
#define MAP_ROOM_2 11246
#define MAP_ROOM_3 11853
#define MAP_ROOM_4 11854
#define MAP_DOOR 1217
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
    Hero = Hero::createHero();


    //创建状态栏
    Sprite* Board = Sprite::create("board.png");
    Board->setPosition(100, 580);
    Board->setScale(0.5f);
    addChild(Board);
    BoardCreate();

    auto BackMusic = BackGroundMusic::create();

    addChild(BackMusic);


    map->addChild(Hero);
    /*monster = EnemyMonster::createMonster();*/
    /*addChild(monster);*/
    scheduleUpdate();
    return true;
}
//当人物受到攻击时，需要调用此函数
void  MapScene::BoardCreate()
{
    BloodCreate();
    MpCreate();
    AcCreate();
}
bool MapScene::isCanReach(float x, float y, int Type_Wall)
{
    bool result;
    int mapX = (int)((x - 16) / 32 +1);//地图宽从1开始
    int mapY = (int)(99 - (y - 16) / 32);//地图长为100
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

bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow,int ValueWall)
{
    int i = 1;
    while (i <= 5)
    {
        if (!isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            Hero->hero->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), ValueWall))
        {

           /* log("i=%d", i);*/
            break;
        }
        else
            i++;

    }

    if (i <= 2)
        return true;//2格范围内有墙
    else
        return false;
}
bool MapScene::WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ValueWall)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1, ValueWall)
        && isCanReach(Hero->hero->getPositionX() + offsetX, Hero->hero->getPositionY() + offsetY, ValueWall))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2, ValueWall)
            && isCanReach(Hero->hero->getPositionX() + offsetX, Hero->hero->getPositionY() + offsetY, ValueWall))))
        && isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), ValueWall))
        return true;
    else
        return false;
}
bool MapScene::JudgeBarrier(float offsetX, float offsetY, char key_arrow)
{
    if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow) * (1 * 16) + ('a' == key_arrow) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow) * (1 * 16) + ('s' == key_arrow) * (-1 * 16), MAP_BARRIER_TREE))
    {
        return true;
    }
    else
        return false;
}
void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2,char key_arrow_3)
{
    RoomIn(offsetX, offsetY, key_arrow_1, key_arrow_2, key_arrow_3, JudgeWhichRoomIn());

}
void MapScene::OpenDoor()
{
    Sprite* runSp[7];
    for (int i = 0; i <= 6; i++)
    {
      
        runSp[i]= Sprite::create("run_6.png");
        runSp[i]->setScale(0.8f);
        map->addChild(runSp[i]);
    }
  
    runSp[0]->setPosition(32 * 37.0f+10, 32 * 92.0f);
    runSp[3]->setPosition(32 * 38.0f + 20, 32 * 52.0f-10);
    runSp[4]->setPosition(32 * 19.0f + 20, 32 * 52.0f-10);
    runSp[1]->setPosition(32 * 52.0f+10, 32 * 80.0f-20);

    runSp[1]->setRotation(-90.0f);
  
    runSp[2]->setPosition(32 * 52.0f + 10, 32 * 62.0f - 20);
    runSp[2]->setRotation(-90.0f);

    runSp[5]->setPosition(32 * 52.0f + 10, 32 * 40.0f - 10);
    runSp[5]->setRotation(-90.0f);

    runSp[6]->setPosition(32 * 52.0f + 10, 32 * 25.0f - 10);
    runSp[6]->setRotation(-90.0f);
    /* 加载图片帧到缓存池 */
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("opendoor.plist", "opendoor.png");

    /* 用辅助工具创建动画 */
    Animation* animation = AnimationUtil::createAnimWithFrameNameAndNum("run_", 6, 10.0f, 1);

    /* 动画也是动作，精灵直接执行动画动作即可 */
    for (int i = 0; i <= 6; i++)
    {

        runSp[i]->runAction(Animate::create(animation));
    }
    
}
void MapScene::CloseDoor()
{
    Sprite* runSp_2[7];
    for (int i = 0; i <= 6; i++)
    {

        runSp_2[i] = Sprite::create("run6.png");
        runSp_2[i]->setScale(0.8f);
        map->addChild(runSp_2[i]);
    }

    runSp_2[0]->setPosition(32 * 37.0f + 10, 32 * 92.0f);
    runSp_2[3]->setPosition(32 * 38.0f + 20, 32 * 52.0f - 10);
    runSp_2[4]->setPosition(32 * 19.0f + 20, 32 * 52.0f - 10);
    runSp_2[1]->setPosition(32 * 52.0f + 10, 32 * 80.0f - 20);

    runSp_2[1]->setRotation(-90.0f);

    runSp_2[2]->setPosition(32 * 52.0f + 10, 32 * 62.0f - 20);
    runSp_2[2]->setRotation(-90.0f);

    runSp_2[5]->setPosition(32 * 52.0f + 10, 32 * 40.0f - 10);
    runSp_2[5]->setRotation(-90.0f);

    runSp_2[6]->setPosition(32 * 52.0f + 10, 32 * 25.0f - 10);
    runSp_2[6]->setRotation(-90.0f);
    /* 加载图片帧到缓存池 */
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("closedoor.plist", "closedoor.png");

    /* 用辅助工具创建动画 */
    Animation* animation = AnimationUtil::createAnimWithFrameNameAndNum("run", 6, 1.0f, 1);

    /* 动画也是动作，精灵直接执行动画动作即可 */
    for (int i = 0; i <= 6; i++)
    {

        runSp_2[i]->runAction(Animate::create(animation));
    }
}

bool MapScene::StateDoor(int ValueWall)
{
    //当它踏上这块启动板
    if (!isCanReach(Hero->hero->getPositionX(), Hero->hero->getPositionY(),ValueWall))
    {
        JudgeOpenTime ++;
        PositionDoor = true;
    }
    if (PositionDoor&& JudgeOpenTime==1)
    {
        CloseDoor();
        Room[NumJudgeWhichRoom(ValueWall)] = 0;
        JudgeOpenTime++;
        
        return true;//此刻房间封锁
    }
    else if(/*monster->isAllDead()*/0)
    {
        OpenDoor();
        PositionDoor = false;
        JudgeOpenTime = 0;
        return false; //此刻房间打开
    }
    else if(JudgeOpenTime>=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int MapScene::JudgeWhichRoomIn()
{
    for (int i = 0; i <= 3; i++)
    {
        if (0 == i&& Room[i])
        {
            return MAP_ROOM_1;
        }
        if (1 == i && Room[i])
        {
            return MAP_ROOM_2;
        }
        if (2 == i && Room[i])
        {
            return MAP_ROOM_3;
        }
        if (3 == i && Room[i])
        {
            return MAP_ROOM_4;
        }
    }

}
int MapScene::NumJudgeWhichRoom(int ValueRoom)
{
    if (ValueRoom == MAP_ROOM_1)
        return 0;
    if (ValueRoom == MAP_ROOM_2)
        return 1;
    if (ValueRoom == MAP_ROOM_3)
        return 2;
    if (ValueRoom == MAP_ROOM_4)
        return 3;
}
void MapScene::RoomIn(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ROOM_NUM)
{
    if (StateDoor(ROOM_NUM))
    {
        if (WhetherHeroMove(offsetX, offsetY, key_arrow_1, key_arrow_2, key_arrow_3, MAP_WALL) && WhetherHeroMove(offsetX, offsetY, key_arrow_1, key_arrow_2, key_arrow_3, MAP_DOOR))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL)
                    && isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_DOOR)
                    )
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        PureHeroMove(offsetX, offsetY);
                    }
                }
            }
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
            if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL)
                && isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_DOOR)
                )
            {
                if (key_arrow_3 != '-')
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        AllMove(offsetX, offsetY);
                    }
                }
                else
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        AllMove(offsetX, offsetY);
                    }
                }
            }
        }
    }
    else
    {
        if (WhetherHeroMove(offsetX, offsetY, key_arrow_1, key_arrow_2, key_arrow_3, MAP_WALL))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL)
                    )
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        PureHeroMove(offsetX, offsetY);
                    }
                }
            }
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
            if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL)
                )
            {
                if (key_arrow_3 != '-')
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        AllMove(offsetX, offsetY);
                    }
                }
                else
                {
                    if (JudgeBarrier(offsetX, offsetY, key_arrow_3) && JudgeBarrier(offsetX, offsetY, key_arrow_1))
                    {
                        AllMove(offsetX, offsetY);
                    }
                }
            }
        }
    }
}
void MapScene::BloodCreate()
{
    //////////////////////////////

    auto loadingBar = ui::LoadingBar::create("blood.png", 100);

    // set the direction of the loading bars progress
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    loadingBar->setPercent(TransPencent(1));
    loadingBar->setScale(0.5f);
    Node::addChild(loadingBar);
    loadingBar->setPosition(Vec2(112,605));
}
void MapScene::MpCreate()
{
    //////////////////////////////

    auto loadingBar = ui::LoadingBar::create("Mp.png", 100);

    // set the direction of the loading bars progress
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    loadingBar->setPercent(TransPencent(2));
    loadingBar->setScale(0.5f);
    Node::addChild(loadingBar);
    loadingBar->setPosition(Vec2(112, 555));
}
void MapScene::AcCreate()
{
    //////////////////////////////

    auto loadingBar = ui::LoadingBar::create("Ac.png", 100);

    // set the direction of the loading bars progress
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    loadingBar->setPercent(TransPencent(2));
    loadingBar->setScale(0.5f);
    Node::addChild(loadingBar);
    loadingBar->setPosition(Vec2(112, 580));
}
float MapScene::TransPencent(int type)
{
    //1为血量 2为蓝条 3 为护甲
    if (type == 1)
    {
        return (Hero->blood / 7 * 100);
    }
    if (type == 2)
    {
        return (Hero->Mp / 180 * 100);
    }
    if (type == 3)
    {
        return (Hero->Ac / 5 * 100);
    }
}