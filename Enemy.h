#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MonsterNumber 10

#include "cocos2d.h"
class EnemyMonster : public cocos2d::Layer
{
public:
    int MonsterType;//С�ֵ�����
    float PositionX, PositionY;//С�ֵ�����λ�õ����꣬��setPosition������������
    int blood;//С�ֵ�Ѫ��
    cocos2d::Sprite* Monster;//С�ֵľ���ʵ�� 
    static EnemyMonster* createMonster();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void MonsterInit();//��ʼ��
    void OriginalPosition();//������ɵ��˵�λ�����꣨δ������
    void start(int type, int positionX, int positionY);//����С�ֵ��������ʼλ��
    void isDead();//С������֮��MonsterType����Ϊ0
    void MoveMonster();//С���ƶ�����
    CREATE_FUNC(EnemyMonster);
    EnemyMonster* monster[MonsterNumber];
    void  MyUpdate(float dt);//����С�ֵ��ƶ�
};


#endif