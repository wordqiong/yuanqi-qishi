#pragma once
#ifndef __Move_Hero_H__
#define __Move_Hero_H__

#include "cocos2d.h"
class MoveHero : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    void update(float delta) override;//利用定时器每一帧更新人物的移动

    
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//记录每一个按键是否被按下
    
    cocos2d::Sprite* hero;
    CREATE_FUNC(MoveHero);
    static MoveHero* sharedLayer;

    
};

#endif



