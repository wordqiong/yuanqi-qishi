
#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MonsterNumber 5


#include "cocos2d.h"
class EnemyMonster : public cocos2d::Layer
{
public:

    bool iscreated[4];//判断4个房间是否生成过怪物
        
    int MonsterType;//小怪的种类

    float PositionX, PositionY;//小怪的生成位置的坐标，由 OriginalPosition（）函数生成

    int blood;//小怪的血量

    int speed;//小怪的速度

    bool isDirectionChange;//判断小怪移动方向是否变化

    bool isStand;//判断小怪是否站立不动

    cocos2d::Sprite* Monster;//小怪的精灵实例 

    int direction;//获取小怪移动的方向

    static EnemyMonster* createMonster();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void MonsterInit();
    
    void monsterInit();//整体初始化

    virtual void OriginalPosition(int RoomNumber);//随机生成敌人的位置坐标（未开发）

    void start(int type, int positionX, int positionY);//设置小怪的种类和起始位置

    void MoveMonster();//小怪移动函数

    CREATE_FUNC(EnemyMonster);

    EnemyMonster* monster[MonsterNumber];

    void  MoveUpdate(float dt);//更新小怪的移动

    void  AttackUpdate(float dt);//更新小怪的攻击

    virtual cocos2d::Animate* createAnimate_move(int MonsterType, int direction, int num);//创建移动动画

    cocos2d::Animate* createAnimate_dead(int MonsterType, int direction, int num);//创建死亡动画
    
    void MonsterResume();

    void isDead();//小怪死亡

    bool isFade;

    bool isAllFade;

    void DeadUpdate(float dt);

    bool isAllDead();//判断所有小怪是否都死亡
  
    void AllMonstersfade();//所有小怪从地图中消失

    bool inAttack[4];//三种小怪的攻击状态

    int AttackTime[4];//三种小怪的攻击间隔


};
#endif