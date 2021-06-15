#include "MoveHero.h"

USING_NS_CC;

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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto myKeyListener = EventListenerKeyboard::create();

    

    hero = Sprite::create("knight.png");
    if (hero == nullptr)
    {
        log("not found");
    }
    else
    {
        hero->setScale(1.0f);
        hero->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
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
        log("%d", keyCode);
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        keys[keyCode] = false;

    };
    int offsetX = 0, offsetY = 0;
    if (keys[leftArrow])
    {
        offsetX = -2;
        is_Move = true;
    }
    if (keys[rightArrow])
    {
        offsetX = 2;
        is_Move = true;
    }
    if (keys[upArrow])
    {
        offsetY = 2;
        is_Move = true;
    }
    if (keys[downArrow])
    {
        offsetY = -2;
        is_Move = true;
    }
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
    hero->runAction(moveTo);
    offsetX = offsetY = 0;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}