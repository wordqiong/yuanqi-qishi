#include "MoveHero.h"
#include "Enemy.h"
USING_NS_CC;
MoveHero* MoveHero::sharedLayer = nullptr;
Scene* MoveHero::createScene()
{
    auto scene = Scene::create();
    auto layer = MoveHero::create();
    scene->addChild(layer);
    return scene;
}
bool MoveHero::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    sharedLayer = this;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto myKeyListener = EventListenerKeyboard::create();
    auto monster=EnemyMonster::createMonster();
    addChild(monster);
    hero = Sprite::create("hero.png");
    if (hero == nullptr)
    {
        log("not found");
    }
    else
    {
        hero->setScale(0.6f);
        hero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(hero);
        scheduleUpdate();
    }
   
        return true;
    
}


void MoveHero::update(float delta) 
{
    Node::update(delta);
    auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D,
        upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = true;
        //log("%d",keyCode);
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = false;

    };
    int offsetX = 0, offsetY = 0;
    if (keys[leftArrow])
    {
        offsetX = -2;
    }
    if (keys[rightArrow])
    {
        offsetX = 2;
    }
    if (keys[upArrow])
    {
        offsetY = 2;
    }
    if (keys[downArrow])
    {
        offsetY = -2;
    }
    auto moveTo = MoveTo::create(1.0/1000, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
    hero->runAction(moveTo);
    offsetX = offsetY = 0;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
}



