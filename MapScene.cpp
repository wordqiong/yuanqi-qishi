#include "MapScene.h"
#include "ui\UIButton.h"
#include<cmath>
using namespace std;
using namespace ui;


#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_ROOM 11853

USING_NS_CC;

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

void MapScene::addGun() {
    Gun* fireGun = Gun::create();
    fireGun->bindSprite(Sprite::create("fireGun.png"));
    fireGun->getSprite()->setPosition(Point(100, 0));//暂时先固定位置
    fireGun->getSprite()->setAnchorPoint(Point(0.5,0.45));
    
    map->addChild(fireGun);

    this->GunsVector.push_back(fireGun);
}

void MapScene::flipped(int direction) {
    switch (direction) {
    case 1:
       this->GunsVector[0]->getSprite()->setFlippedY(true);
       break;
    case 2:
        this->GunsVector[0]->getSprite()->setFlippedY(false);
    }
}

// on "init" you need to initialize your instance
//bool MapScene::init()
//{
//    if (!Scene::init())
//    {
//        return false;
//    }
//    //将出生点设置在窗口下
//    map = TMXTiledMap::create("map.tmx");
//    layer2 = map->getLayer("layer2");
//    layer2->setVisible(false);
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    if (map == nullptr)
//    {
//        log("tile map not found");
//    }
//    else
//    {
//        map->setAnchorPoint(Vec2::ZERO);
//        map->setPosition(0, -32 * (100 - 18));
//        addChild(map);
//    }
//    //创建hero，将它放在地图中央
//    heroInit();
//   /* hero = Sprite::create("knight.png");
//    map->addChild(hero);
//    hero->setAnchorPoint(Vec2::ZERO);
//    hero->setPosition(32 * 10.0f, 32 * 92.0f);*/
//
//    this->addGun();//生成枪支    对了，在操作枪支时还要先锁定需要操作的枪支，这个函数后续再加
//    this->GunsVector[0]->getSprite()->setPosition(Point(this->hero->getPositionX()+18 , this->hero->getPositionY() + 17));
//   
//
//    //建一个怪试验一下
//    Monster* monster = Monster::create();
//    monster->bindSprite(Sprite::create("MonsterShooter.png"));
//    monster->getSprite()->setPosition(Point(this->hero->getPositionX() + 120, this->hero->getPositionY() + 90));
//    map->addChild(monster);
//    this->MonsterVector.push_back(monster);
//    
//
//
//    //点击开枪
//
//    /*auto closeItem = MenuItemImage::create(
//        "MonsterShooter.png",
//        "CloseSelected.png",
//        CC_CALLBACK_1(MapScene::menuCloseCallback, this));*/
//
//    //if (closeItem == nullptr ||
//    //    closeItem->getContentSize().width <= 0 ||
//    //    closeItem->getContentSize().height <= 0)
//    //{
//    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    //}
//    //else
//    //{
//    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
//    //    float y = origin.y + closeItem->getContentSize().height / 2;
//    //    closeItem->setPosition(Vec2(x, y));
//    //}
//
//    //// create menu, it's an autorelease object
//    //auto menu = Menu::create(closeItem, NULL);
//    //menu->setPosition(Vec2::ZERO);
//    //this->addChild(menu, 1);
//
//    //按住开枪
//    Button* ShootButton = Button::create("ShootButton2.png", "ShootButton.png");
//    float x = origin.x + visibleSize.width - ShootButton->getContentSize().width / 2;
//    float y = origin.y + ShootButton->getContentSize().height / 2;
//    ShootButton->setPosition(Vec2(x,y));
//    ShootButton->addTouchEventListener(CC_CALLBACK_2(MapScene::touchCallBack,this));
//    this->addChild(ShootButton);
//   // //posted by mxy
//
//
//    scheduleUpdate();
//    return true;
//}

bool MapScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //将出生点设置在窗口下
    map = TMXTiledMap::create("map.tmx");
    layer2 = map->getLayer("layer2");
    layer2->setVisible(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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
    heroInit();

    this->addGun();
    //生成枪支    对了，在操作枪支时还要先锁定需要操作的枪支，这个函数后续再加
    this->GunsVector[0]->getSprite()->setPosition(Point(this->hero->getPositionX()+18 , this->hero->getPositionY() + 17));
   

    //建一个怪试验一下
    Monster* monster = Monster::create();
    monster->bindSprite(Sprite::create("MonsterShooter.png"));
    monster->getSprite()->setPosition(Point(this->hero->getPositionX() + 120, this->hero->getPositionY() + 90));
    map->addChild(monster);
    this->MonsterVector.push_back(monster);

    //按住开枪
    Button* ShootButton = Button::create("ShootButton2.png", "ShootButton.png");
    float x = origin.x + visibleSize.width - ShootButton->getContentSize().width / 2;
    float y = origin.y + ShootButton->getContentSize().height / 2;
    ShootButton->setPosition(Vec2(x,y));
    ShootButton->addTouchEventListener(CC_CALLBACK_2(MapScene::touchCallBack,this));
    this->addChild(ShootButton);
//   // //posted by mxy

    scheduleUpdate();
    return true;
}

//射击按钮的回调
void MapScene::touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        this->GunsVector.at(0)->is_fire = true;
        break;

    case Widget::TouchEventType::MOVED:
       
        break;

    case Widget::TouchEventType::ENDED:
        this->GunsVector.at(0)->is_fire = false;
        break;

    case Widget::TouchEventType::CANCELED:
       
        break;

    default:
        break;
    }

}

//posted by mxy

void  MapScene::heroInit()
{
    hero = Sprite::create("knight.png");
    direction = 2;//初始朝向设置为向右
    isStand = true;//初始状态为站立
    isDirectionChange = false;
    map->addChild(hero);
    hero->setAnchorPoint(Vec2::ZERO);
    hero->setPosition(32 * 10.0f, 32 * 92.0f);//创建hero，将它放在地图中央
}

Animate* MapScene::createAnimate(int direction, int num)
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

void MapScene::HeroResume()
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


    this->GunsVector[0]->getSprite()->setPosition(Point(this->hero->getPositionX() + 45, this->hero->getPositionY() + 17));

    //开枪
    if (!this->GunsVector.at(0)->BulletsVector.empty()) {
                    for (auto Bullet : this->GunsVector.at(0)->BulletsVector) {
                        Bullet->MovebyLine();
                        if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX()-5, Bullet->getSprite()->getPositionY()-5, MAP_WALL))) {
                            this->GunsVector.at(0)->removeChild(Bullet,true);
                        }
                    }
                }
        //确定开枪方向（旋转）
    for (auto monster : this->MonsterVector) {
        
                    this->GunsVector.at(0)->revolve(this->GunsVector.at(0)->bindEnemy(monster));
                }


    this->flipped(this->direction);//枪随人物反转


    offsetX = offsetY = 0;

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//void MapScene::update(float delta)
//{
//    Node::update(delta);
//    auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D,
//        upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;
//    auto listener = EventListenerKeyboard::create();
//    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
//    {
//        keys[keyCode] = true;
//        log("%d", keyCode);
//    };
//
//    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
//    {
//        keys[keyCode] = false;
//
//    };
//    int offsetX = 0, offsetY = 0;
//    if (keys[leftArrow])
//    {
//        if (direction == 2)
//        {
//            isDirectionChange = true;
//        }
//        direction = 1;//代表向左
//        if (keys[upArrow] || keys[downArrow])
//        {
//            offsetX = -1.41;
//            if (keys[upArrow])
//            {
//                FinalMove(offsetX, offsetY, 'a', 'd');
//            }
//            if (keys[downArrow])
//            {
//                FinalMove(offsetX, offsetY, 'a', 'd');
//            }
//        }
//        else
//        {
//            offsetX = -4;
//            FinalMove(offsetX, offsetY, 'a', 'd');
//        }
//
//    }
//    if (keys[rightArrow])
//    {
//        if (direction == 1)
//        {
//            isDirectionChange = true;
//        }
//        direction = 2;//代表向右
//        if (keys[upArrow] || keys[downArrow])
//        {
//            offsetX = 1.41;
//            if (keys[upArrow])
//            {
//                FinalMove(offsetX, offsetY, 'd', 'a');
//            }
//            if (keys[downArrow])
//            {
//                FinalMove(offsetX, offsetY, 'd', 'a');
//            }
//        }
//        else
//        {
//            offsetX = 4;
//            FinalMove(offsetX, offsetY, 'd', 'a');
//        }
//
//
//    }
//    if (keys[upArrow])
//    {
//        if (keys[rightArrow] || keys[leftArrow])
//        {
//            offsetY = 1.41;
//            if (keys[rightArrow])
//            {
//                FinalMove(offsetX, offsetY, 'w', 's');
//
//                if (keys[leftArrow])
//                {
//                    FinalMove(offsetX, offsetY, 'w', 's');
//                }
//            }
//            else
//            {
//                offsetY = 4;
//                FinalMove(offsetX, offsetY, 'w', 's');
//            }
//
//
//        }
//        if (keys[downArrow])
//        {
//            if (keys[rightArrow] || keys[leftArrow])
//            {
//                offsetY = -1.41;
//                if (keys[rightArrow])
//                {
//                    FinalMove(offsetX, offsetY, 's', 'w');
//                }
//                if (keys[leftArrow])
//                {
//                    FinalMove(offsetX, offsetY, 's', 'w');
//                }
//            }
//            else
//            {
//                offsetY = -4;
//                FinalMove(offsetX, offsetY, 's', 'w');
//            }
//
//        }
//        if (offsetX == 0 && offsetY == 0)
//        {
//            HeroResume();
//            isStand = true;
//        }
//
//        ////开火
//        // if (this->GunsVector.at(0)->is_fire == true) {
//        //     this->GunsVector.at(0)->Fire ();
//        // }
//
//        this->GunsVector[0]->getSprite()->setPosition(Point(this->hero->getPositionX() + 45, this->hero->getPositionY() + 17));
//        log("Y"); log("%d", this->GunsVector[0]->getSprite()->getPositionY());
//
//        if (!this->GunsVector.at(0)->BulletsVector.empty()) {
//            for (auto Bullet : this->GunsVector.at(0)->BulletsVector) {
//                Bullet->MovebyLine();
//                /*if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX()+2, Bullet->getSprite()->getPositionY()+0, MAP_WALL))) {
//                    this->GunsVector.at(0)->removeChild(Bullet);
//                }*/
//            }
//        }
//
//        for (auto monster : this->MonsterVector) {
//
//            this->GunsVector.at(0)->revolve(this->GunsVector.at(0)->bindEnemy(monster));
//        }
//
//
//        offsetX = offsetY = 0;
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//
//    }
//}

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
    auto* animate = createAnimate(direction, 3);
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(map->getPositionX() - offsetX, map->getPositionY() - offsetY));
    if (isStand == true || isDirectionChange == true)
    {
        HeroResume();
        hero->runAction(animate);
        isStand = false;
        isDirectionChange = false;
    }
    map->runAction(moveTo);
}
void MapScene::PureHeroMove(float offsetX, float offsetY)
{
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
    hero->runAction(moveTo);
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
        if (!isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            hero->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), MAP_WALL))
        {

            /* log("i=%d", i);*/
            break;
        }
        else
            i++;

    }

    if (i <= 5)
        return true;//五格范围内有墙
    else
        return false;
}


void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1)
        && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2)
            && isCanReach(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY, MAP_WALL))))
        && isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
    {
        if (key_arrow_3 != '-')
        {
            if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
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
        if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(hero->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
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

//void MapScene::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    this->GunsVector.at(0)->Fire();//开火函数里就是createBullets和移动函数，稍后再改
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//}


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