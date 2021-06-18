#include "MapScene.h"
#include "ui/CocosGUI.h"
#include "AnimationUtil.h"
#include "BackGroundMusic.h"
#include "Enemy.h"
#include"box.h"
#include"Boss.h"
#include"potion.h"
#include "ui\UIButton.h"
#include<cmath>
#include<string>

USING_NS_CC;
using namespace ui;

MapScene* MapScene::sharedScene = nullptr;
Scene* MapScene::createScene()
{
    return MapScene::create();
}


void MapScene::addPotion() {
    Potion* potion = Potion::create();
    string load2 = std::to_string(potion->type);
    potion->final_load = potion->load1 + load2 + potion->load3;
    potion->bindSprite(Sprite::create(potion->final_load));

    potion->getSprite()->setPosition(Point(this->Hero->hero->getPositionX() + 200, this->Hero->hero->getPositionY() + 100));
    this->PotionVector.push_back(potion);
    this->map->addChild(potion);
}

void MapScene::addGun() {
    Gun* fireGun = Gun::create();
    fireGun->bindSprite(Sprite::create("fireGun.png"));
    fireGun->getSprite()->setPosition(Point(100, 0));//暂时先固定位置
    fireGun->getSprite()->setAnchorPoint(Point(0.5, 0.45));
    fireGun->is_can_be_used = false;//先直接被绑定
    this->Hero->GunOfHero.push_back(fireGun);//插到hero枪组里
    map->addChild(fireGun);

    this->GunsVector.push_back(fireGun);
}

void MapScene::flipped(int direction) {
    if (this->Hero->GunOfHero.size() == 1) {
        switch (direction) {
            case 1:
                this->Hero->GunOfHero[0]->getSprite()->setFlippedY(true);
                break;
            case 2:
                this->Hero->GunOfHero[0]->getSprite()->setFlippedY(false);
        }
    }
    if (this->Hero->GunOfHero.size() == 2) {
        switch (direction) {
            case 1:
                this->Hero->GunOfHero[1]->getSprite()->setFlippedY(true);
                break;
            case 2:
                this->Hero->GunOfHero[1]->getSprite()->setFlippedY(false);
        }
    }
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance

void MapScene::addShootButton()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Button* ShootButton = Button::create("ShootButton2.png", "ShootButton.png");
    float x = origin.x + visibleSize.width - ShootButton->getContentSize().width / 2;
    float y = origin.y + ShootButton->getContentSize().height / 2;
    ShootButton->setPosition(Vec2(x, y));
    ShootButton->addTouchEventListener(CC_CALLBACK_2(MapScene::touchCallBack, this));
    this->addChild(ShootButton);
    
}

void MapScene::addsignalItem()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    signalItem = MenuItemImage::create(
        "signalButton.png",
        "shootButton.png",
        CC_CALLBACK_1(MapScene::menuCloseCallback, this));
    signalItem->setVisible(false);

    if (signalItem == nullptr ||
        signalItem->getContentSize().width <= 0 ||
        signalItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - signalItem->getContentSize().width / 2;
        float y = origin.y + signalItem->getContentSize().height / 2;
        signalItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(signalItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

}

void MapScene::addchangGunItem()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    changGunItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MapScene::changeGunCallback, this));

    if (changGunItem == nullptr ||
        changGunItem->getContentSize().width <= 0 ||
        changGunItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - changGunItem->getContentSize().width / 2;
        float y = origin.y + changGunItem->getContentSize().height / 2;
        changGunItem->setPosition(Vec2(x, y + 150));
    }

    // create menu, it's an autorelease object
    auto menu2 = Menu::create(changGunItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);
}

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


    box_create = map->getLayer("box_create");
    box_create->setVisible(false);


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

    for (int i = 0; i <= 4; i++)
        isMonsterCreated[i] = false;

    //创建hero，将它放在地图中央
    Hero = Hero::createHero();
    addChild(Hero);
    Gun* fireGun = Gun::create();
    fireGun->bindSprite(Sprite::create("fireGun.png"));
    fireGun->getSprite()->setPosition(Point(MapScene::sharedScene->Hero->hero->getPositionX() - 200, MapScene::sharedScene->Hero->hero->getPositionY() - 100));//暂时先固定位置
    fireGun->getSprite()->setAnchorPoint(Point(0.5, 0.45));
    MapScene::sharedScene->map->addChild(fireGun);
    MapScene::sharedScene->GunsVector.push_back(fireGun);
    
    this->addGun();
    this->addPotion();//生成血瓶
    addShootButton();//初始化射击按钮
    addsignalItem();//初始化信号按钮
    addchangGunItem();//初始化换枪按钮
    schedule(CC_SCHEDULE_SELECTOR(MapScene::CreateUpdate));
    schedule(CC_SCHEDULE_SELECTOR(MapScene::GunUpdate));

    //创建状态栏
    Sprite* Board = Sprite::create("board.png");
    Board->setPosition(100, 580);
    Board->setScale(0.5f);
    addChild(Board);
    BoardCreate();
    auto BackMusic = BackGroundMusic::create();
    addChild(BackMusic);

    



    return true;
}


//射击按钮的回调
void MapScene::touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (this->Hero->GunOfHero.size() == 1) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                this->Hero->GunOfHero[0]->is_fire = true;
                break;

            case Widget::TouchEventType::MOVED:

                break;

            case Widget::TouchEventType::ENDED:
                this->Hero->GunOfHero[0]->is_fire = false;
                break;

            case Widget::TouchEventType::CANCELED:

                break;

            default:
                break;
        }
    }
    if (this->Hero->GunOfHero.size() == 2) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                this->Hero->GunOfHero[1]->is_fire = true;
                break;

            case Widget::TouchEventType::MOVED:

                break;

            case Widget::TouchEventType::ENDED:
                this->Hero->GunOfHero[1]->is_fire = false;
                break;

            case Widget::TouchEventType::CANCELED:

                break;

            default:
                break;
        }
    }

}


bool MapScene::isCanReach(float x, float y, char name)
{
    int mapX = (int)((x - 16) / 32 + 1);//地图宽从1开始
    int mapY = (int)(99 - (y - 16) / 32);//地图长为100
    if (mapX < 0 || mapX>73 || mapY < 0 || mapY>99)
    {
        return false;
    }
    int tileGid = box_create->getTileGIDAt(Vec2(mapX, mapY));
    auto properties = map->getPropertiesForGID(tileGid);
    auto mid = properties.asValueMap().at("box");
    if (mid.asString().compare("true") == 0)
    {
        //TMXLayer* barrier = map->getLayer("box_create");
        //barrier->removeTileAt(Vec2(mapX, mapY));
        log("box is using");
        return false;
    }
    else
    {
        log("box is using");
        return true;
    }

}



void MapScene::GunUpdate(float dt)
{
    ///* 加载图片帧到缓存池 */
    //SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    //frameCache->addSpriteFramesWithFile("bullet.plist", "bullet.png");

    ///* 用辅助工具创建动画 */
    //animation_bullet = AnimationUtil::createAnimWithFrameNameAndNum("bullet", 6, 1.0f, 1);

    //

    /* 动画也是动作，精灵直接执行动画动作即可 */
    //枪械跟随   

    for (auto gun : this->Hero->GunOfHero) {
        gun->getSprite()->setPosition(Point(this->Hero->hero->getPositionX() + 45, this->Hero->hero->getPositionY() + 17));
    }


    //开枪（目前还是map里的枪组，等会换成hero的枪组）有一把枪时第0个开枪，有两把枪时第1个开枪
    if (this->Hero->GunOfHero.size() == 1) {
        if (!this->Hero->GunOfHero[0]->BulletsVector.empty()) {
            for (auto Bullet : this->Hero->GunOfHero[0]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() - 5, Bullet->getSprite()->getPositionY() - 5, MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
    }
    if (this->Hero->GunOfHero.size() == 2) {
        if (!this->Hero->GunOfHero[1]->BulletsVector.empty()) {
            for (auto Bullet : this->Hero->GunOfHero[1]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() - 5, Bullet->getSprite()->getPositionY() - 5, MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
        if (!this->Hero->GunOfHero[0]->BulletsVector.empty()) {
            for (auto Bullet : this->Hero->GunOfHero[0]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() + 20 * (Bullet->numx / Bullet->S), Bullet->getSprite()->getPositionY() + 20 * (Bullet->numy / Bullet->S), MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
    }

    //确定开枪方向（旋转）
    if (Hero->RoomPosition > 0)
    {
        if (!this->monster->isAllDead()) {
            if (this->Hero->GunOfHero.size() == 1 && this->Hero->bindedMonster != NULL) {

                this->Hero->GunOfHero[0]->revolve(this->Hero->GunOfHero[0]->bindEnemy(this->Hero->bindedMonster));
                if (this->Hero->bindedMonster->Monster->getPositionX() - this->Hero->GunOfHero[0]->getSprite()->getPositionX() >= 0) {
                    if (this->Hero->direction == 1) {
                        this->Hero->isDirectionChange = true;
                    }
                    this->Hero->direction = 2;
                }
                if (this->Hero->bindedMonster->Monster->getPositionX() - this->Hero->GunOfHero[0]->getSprite()->getPositionX() < 0) {
                    if (this->Hero->direction == 2) {
                        this->Hero->isDirectionChange = true;
                    }
                    this->Hero->direction = 1;
                }
            }
            else if (this->Hero->GunOfHero.size() == 2 && this->Hero->bindedMonster != NULL) {
                this->Hero->GunOfHero[1]->revolve(this->Hero->GunOfHero[1]->bindEnemy(this->Hero->bindedMonster));
                if (this->Hero->bindedMonster->Monster->getPositionX() - this->Hero->GunOfHero[1]->getSprite()->getPositionX() >= 0) {
                    if (this->Hero->direction == 1) {
                        this->Hero->isDirectionChange = true;
                    }
                    this->Hero->direction = 2;
                }
                if (this->Hero->bindedMonster->Monster->getPositionX() - this->Hero->GunOfHero[1]->getSprite()->getPositionX() < 0) {
                    if (this->Hero->direction == 2) {
                        this->Hero->isDirectionChange = true;
                    }
                    this->Hero->direction = 1;
                }

            }
        }
    }



    //判断什么时候（捡枪）和血瓶
    if (!this->PotionVector.empty()) {
        for (auto potion : this->PotionVector) {
            //如果没被使用过
            if (potion->is_can_be_used) {
               
                int x = (int)potion->getSprite()->getPositionX() - 30 - (int)Hero->hero->getPositionX();
                int y = (int)potion->getSprite()->getPositionY() - 30 - (int)Hero->hero->getPositionY();
                int s_s = x * x + y * y;

                int s = (int)sqrt((float)s_s);


                if (s <= 40) {

                    this->BindedPotion = potion;
                    this->is_Bind_Potion = true;
                    this->signalItem->setVisible(true);
                }
                else {
                    this->is_Bind_Potion = false;
                    this->signalItem->setVisible(false);
                }
            }
        }
    }

    for (auto gun : this->GunsVector) {
        if (gun->is_can_be_used) {
            int x = (int)gun->getSprite()->getPositionX() - 30 - (int)Hero->hero->getPositionX();
            int y = (int)gun->getSprite()->getPositionY() - 30 - (int)Hero->hero->getPositionY();
            int s_s = x * x + y * y;

            int s = (int)sqrt((float)s_s);
            /*log("%d", s)*/;
            if (s <= 40) {
                this->BindedGun = gun;
                this->is_Bind_Gun = true;
                this->signalItem->setVisible(true);
            }
            else {
                this->is_Bind_Gun = false;
                if (!this->is_Bind_Potion) {
                    this->signalItem->setVisible(false);
                }

            }
        }
    }

    //子弹与怪物碰撞
    if (Hero->RoomPosition > 0&&!monster->isAllDead())
    {
        for (int i = 0; i < MonsterNumber; i++) {
            if (monster->monster[i]->blood > 0) {
                if (this->Hero->GunOfHero.size() == 1) {
                    if (!this->Hero->GunOfHero[0]->BulletsVector.empty()) {
                        for (auto Bullet : this->Hero->GunOfHero[0]->BulletsVector) {
                            if (!Bullet->isNeedFade) {
                                if (Bullet->is_hit_Monster(monster->monster[i])) {
                                    Bullet->isNeedFade = true;
                                   
                                  
                                  /*  Bullet->runAction(Animate::create(animation_bullet));*/
                         
                                    monster->monster[i]->blood -= 3;

                                }
                            }
                        }
                    }
                }
                if (this->Hero->GunOfHero.size() == 2) {
                    if (!this->Hero->GunOfHero[1]->BulletsVector.empty()) {
                        for (auto Bullet : this->Hero->GunOfHero[1]->BulletsVector) {
                            if (!Bullet->isNeedFade) {
                                if (Bullet->is_hit_Monster(monster->monster[i])) {
                                    Bullet->isNeedFade = true;
                                    Bullet->getSprite()->setVisible(false);
                                    monster->monster[i]->blood -= 3;

                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
 
    if (this->Hero->RoomPosition == 0 || this->monster->isAllDead()) {

        if (this->Hero->direction == 1) {
            for (auto gun : this->Hero->GunOfHero) {

                gun->getSprite()->setRotation(180);
                gun->shootVector = Point(-10, 0);
            }
        }
        if (this->Hero->direction == 2) {
            for (auto gun : this->Hero->GunOfHero) {
                gun->getSprite()->setRotation(0);
                gun->shootVector = Point(10, 0);
            }
        }
    }



    ////怪物死亡
    //for (auto monster : this->MonsterVector) {
    //    if (monster->isAlive) {
    //        if (monster->blood <= 0) {
    //            monster->isAlive = false;
    //            monster->getSprite()->setVisible(false);//精灵不可见
    //            this->num_of_alive_monster -= 1;//活的怪物数量减一
    //           //此处 可以加个死亡动画
    //            //在原位置播放 （一次） 动画
    //        }
    //    }
    //}


    //怪物死光后，枪解除绑定的怪物，设置它的方向向量为初始值

    




    //枪随人物反转
    this->flipped(this->Hero->direction);

    //只显示一把枪
    if (this->Hero->GunOfHero.size() == 2) {
        this->Hero->GunOfHero[0]->getSprite()->setVisible(false);
        this->Hero->GunOfHero[1]->getSprite()->setVisible(true);
    }

}
//whether create
void MapScene::CreateUpdate(float dt)
{
   
    if (Hero->RoomPosition != 0 && isMonsterCreated[Hero->RoomPosition] == false)
    {
        monster = EnemyMonster::createMonster();
        addChild(monster);
        box[Hero->RoomPosition] = Box::createBox();
        addChild(box[Hero->RoomPosition]);
        isMonsterCreated[Hero->RoomPosition] = true;
        if (Hero->RoomPosition == 4)
        {
            boss = Boss::createBoss();
            addChild(boss);
        }
    }

}


//信号按钮的回调,让判断到人在旁边时才显示信号按钮这样就不会多次删除
void MapScene::menuCloseCallback(Ref* pSender)
{
    if (this->is_Bind_Potion) {
        this->BindedPotion->setVisible(false);
        this->BindedPotion->is_can_be_used = false;
        this->is_Bind_Potion = false;
        this->signalItem->setVisible(false);//药水使用后隐藏信号按钮
        //加血加蓝之后加函数

    }
    if (this->is_Bind_Gun) {
        this->BindedGun->is_can_be_used = false;
        this->Hero->addGun(this->BindedGun);//枪插入hero的枪组
        this->is_Bind_Gun = false;
        this->signalItem->setVisible(false);//捡起枪后隐藏信号按钮
    }
}

void MapScene::changeGunCallback(cocos2d::Ref* pSender) {
    if (this->Hero->GunOfHero.size() == 2) {
        vector<Gun*> changeVector;
        changeVector.push_back(this->Hero->GunOfHero[0]);
        this->Hero->GunOfHero[0] = this->Hero->GunOfHero[1];
        this->Hero->GunOfHero[1] = changeVector[0];

    }

}


//当人物受到攻击时，需要调用此函数

bool MapScene::isCanReach(float x, float y, int Type_Wall)
{
    bool result;
    int mapX = (int)((x - 16) / 32 + 1);//地图宽从1开始
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

bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow, int ValueWall)
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
    if (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow) * (1 * 16) + ('a' == key_arrow) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow) * (1 * 16) + ('s' == key_arrow) * (-1 * 16), MAP_BARRIER_TREE)
        && (isCanReach(Hero->hero->getPositionX() + offsetX + ('d' == key_arrow) * (1 * 16) + ('a' == key_arrow) * (-1 * 16), Hero->hero->getPositionY() + offsetY + ('w' == key_arrow) * (1 * 16) + ('s' == key_arrow) * (-1 * 16))))
    {
        return true;
    }
    else
        return false;
}
void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{

    RoomIn(offsetX, offsetY, key_arrow_1, key_arrow_2, key_arrow_3, JudgeWhichRoomIn());

}
void MapScene::OpenDoor()
{
    Sprite* runSp[7];
    for (int i = 0; i <= 6; i++)
    {

        runSp[i] = Sprite::create("run_6.png");
        runSp[i]->setScale(0.8f);
        map->addChild(runSp[i]);
    }

    runSp[0]->setPosition(32 * 37.0f + 10, 32 * 92.0f);
    runSp[3]->setPosition(32 * 38.0f + 20, 32 * 52.0f - 10);
    runSp[4]->setPosition(32 * 19.0f + 20, 32 * 52.0f - 10);
    runSp[1]->setPosition(32 * 52.0f + 10, 32 * 80.0f - 20);

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
    if (!isCanReach(Hero->hero->getPositionX(), Hero->hero->getPositionY(), ValueWall))
    {
        JudgeOpenTime++;
        PositionDoor = true;
    }
    if (PositionDoor && JudgeOpenTime == 1)
    {
        CloseDoor();
        Room[NumJudgeWhichRoom(ValueWall)] = 0;
        JudgeOpenTime++;

        return true;//此刻房间封锁
    }
    else if (Hero->RoomPosition!=0&&monster->isAllDead())
    {
        OpenDoor();
        PositionDoor = false;
        JudgeOpenTime = 0;
        return false; //此刻房间打开
    }
    else if (JudgeOpenTime >= 1)
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
        if (0 == i && Room[i])
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




//当人物受刚进入场景需要调用此函数
void  MapScene::BoardCreate()
{
    Boardupdate();
    Node::addChild(BloodLoadingBar);
    BloodLoadingBar->setPosition(Vec2(112, 605));

    Node::addChild(MpLoadingBar);
    MpLoadingBar->setPosition(Vec2(112, 555));

    Node::addChild(AcLoadingBar);
    AcLoadingBar->setPosition(Vec2(112, 580));
}

void  MapScene::Boardupdate()
{
    BloodCreate();
    MpCreate();
    AcCreate();
}
void MapScene::BloodCreate()
{
    //////////////////////////////

    BloodLoadingBar = ui::LoadingBar::create("blood.png", 100);

    // set the direction of the loading bars progress
    BloodLoadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    BloodLoadingBar->setPercent(TransPencent(1));
    BloodLoadingBar->setScale(0.5f);

}
void MapScene::MpCreate()
{
    //////////////////////////////

    MpLoadingBar = ui::LoadingBar::create("Mp.png", 100);

    // set the direction of the loading bars progress
    MpLoadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    MpLoadingBar->setPercent(TransPencent(2));
    MpLoadingBar->setScale(0.5f);

}
void MapScene::AcCreate()
{
    //////////////////////////////

    AcLoadingBar = ui::LoadingBar::create("Ac.png", 100);

    // set the direction of the loading bars progress
    AcLoadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    // something happened, change the percentage of the loading bar
    AcLoadingBar->setPercent(TransPencent(2));
    AcLoadingBar->setScale(0.5f);

}