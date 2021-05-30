#include "MapScene.h"
#define MAP_SIZE 32*100
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

// on "init" you need to initialize your instance
bool MapScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //add map to the scene
    map = TMXTiledMap::create("map.tmx");
    if (map == nullptr)
    {
        log("tile map not found");
    }
    else
    {
        map->setAnchorPoint(Vec2::ZERO);
       map->setPosition(0,-32*(100-18) );
        addChild(map);
    }
    //下面为测试内容
    size = Director::getInstance()->getVisibleSize();
    sprite = Sprite::create("sprite.png");
    map->addChild(sprite);
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(32*10.0f, 32*92.0f);
        MapMove();
    return true;
}
void MapScene::MapMove()
{
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* e)
    {
        log("key,%d", code);
        switch (code)
        {
            case EventKeyboard::KeyCode::KEY_S:
                    y += 1;
                    map->setPosition(0 + x * 32, -32 * (100 - 18) + y*32);
                    sprite->setPosition(32 * 10.0 - x * 32, 32 * 92.0 - y * 32);
               
               
                break;
            case EventKeyboard::KeyCode::KEY_D:
                x -= 1;
                map->setPosition(0+x*32, -32 * (100 - 18) + y * 32);
                sprite->setPosition(32 * 10.0 - x * 32, 32 * 92.0 - y * 32);
                break;
            case EventKeyboard::KeyCode::KEY_W:
                y -= 1;
                map->setPosition(0 + x * 32, -32 * (100 - 18) + y * 32);
                sprite->setPosition(32 * 10.0 - x * 32, 32 * 92.0 - y * 32);
                break;
            case EventKeyboard::KeyCode::KEY_A:
                x += 1;
                map->setPosition(0 + x * 32, -32 * (100 - 18) + y * 32);
                sprite->setPosition(32 * 10.0 - x * 32, 32 * 92.0 - y * 32);
                break;
            default:
                break;
        }

    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
}



