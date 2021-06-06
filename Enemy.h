#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MonsterNumber 10

#include "cocos2d.h"
class EnemyMonster : public cocos2d::Layer
{
public:
    int MonsterType;//小怪的种类
    float PositionX, PositionY;//小怪的生成位置的坐标，由setPosition（）函数生成
    int blood;//小怪的血量
    cocos2d::Sprite* Monster;//小怪的精灵实例 
    static EnemyMonster* createMonster();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void MonsterInit();//初始化
    void OriginalPosition();//随机生成敌人的位置坐标（未开发）
    void start(int type, int positionX, int positionY);//设置小怪的种类和起始位置
    void isDead();//小怪死亡之后将MonsterType重置为0
    void MoveMonster();//小怪移动函数
    CREATE_FUNC(EnemyMonster);
    EnemyMonster* monster[MonsterNumber];
    void  MyUpdate(float dt);//更新小怪的移动
};


#endif