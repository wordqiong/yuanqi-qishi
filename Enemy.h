
#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MonsterNumber 10

#include "cocos2d.h"
class EnemyMonster : public cocos2d::Layer
{
public:
    int MonsterType;//С�ֵ�����

    float PositionX, PositionY;//С�ֵ�����λ�õ����꣬�� OriginalPosition������������

    int blood;//С�ֵ�Ѫ��

    int speed;//С�ֵ��ٶ�

    bool isDirectionChange;//�ж�С���ƶ������Ƿ�仯

    bool isStand;//�ж�С���Ƿ�վ������

    cocos2d::Sprite* Monster;//С�ֵľ���ʵ�� 

    int direction;//��ȡС���ƶ��ķ���

    static EnemyMonster* createMonster();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void MonsterInit();//��ʼ��

    void OriginalPosition();//������ɵ��˵�λ�����꣨δ������

    void start(int type, int positionX, int positionY);//����С�ֵ��������ʼλ��

    virtual void isDead();//С������֮��MonsterType����Ϊ0

    void MoveMonster();//С���ƶ�����

    CREATE_FUNC(EnemyMonster);

    EnemyMonster* monster[MonsterNumber];

    void  MoveUpdate(float dt);//����С�ֵ��ƶ�

    bool inAttack();

    cocos2d::Animate* createAnimate(int MonsterType, int direction, int num);//�����ƶ�����

    void MonsterResume();

};
#endif