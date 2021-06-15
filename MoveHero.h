#pragma once
#ifndef __Move_Hero_H__
#define __Move_Hero_H__

#include "cocos2d.h"
class MoveHero : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    void update(float delta) override;


    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

    cocos2d::Sprite* hero;
    CREATE_FUNC(MoveHero);

    bool is_Move=false;


};

#endif

