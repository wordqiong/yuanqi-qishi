#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "SafeRoomMove.h"
USING_NS_CC;
Scene* SecondScene::createScene() 
{
	Scene* scene = Scene::create();

	SecondScene* layer = SecondScene::create();

	scene->addChild(layer);

	return scene;
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool SecondScene::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("2222.png");
    //创建返回初始界面的按钮
    auto InitialBack = MenuItemImage::create(
        "initialBack.png",
        "initialBack.png",
        CC_CALLBACK_1(SecondScene::menuInitialBackCallback, this));

    InitialBack->setScale(0.55f);

    if (InitialBack == nullptr ||
        InitialBack->getContentSize().width <= 0 ||
        InitialBack->getContentSize().height <= 0)
    {
        problemLoading("'initialBack.png' and 'initialBack.png'");
    }
    else
    {
        float x = origin.x + InitialBack->getContentSize().width / 3-10;
        float y = origin.y + InitialBack->getContentSize().height / 4+10 ;
        InitialBack->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(InitialBack, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    //创建开始移动的按钮
    auto StartMove = MenuItemImage::create(
        "start.png",
        "start.png",
        CC_CALLBACK_1(SecondScene::menuStartGameCallback, this));

    StartMove->setScale(0.51f);

    if (StartMove == nullptr ||
        StartMove->getContentSize().width <= 0 ||
        StartMove->getContentSize().height <= 0)
    {
        problemLoading("'start.png' and 'start.png'");
    }
    else
    {
        float x1 = origin.x + StartMove->getContentSize().width*4  + 82;
        float y1 = origin.y + StartMove->getContentSize().height / 4 + 4;
        StartMove->setPosition(Vec2(x1, y1));
    }
    auto menu_2 = Menu::create(StartMove, NULL);
    menu_2->setPosition(Vec2::ZERO);
    this->addChild(menu_2, 1);


    sprite->setScale(0.51f);
    if (sprite == nullptr)
    {
        problemLoading("'2222.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

	return true;
}
void SecondScene::menuInitialBackCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(HelloWorld::createScene());

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

}
void SecondScene::menuStartGameCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(SafeRoomMove::createScene());

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

}