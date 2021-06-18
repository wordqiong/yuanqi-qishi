
#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MonsterNumber 10


#include "cocos2d.h"
class EnemyMonster : public cocos2d::Layer
{
public:

    bool iscreated[4];//�ж�4�������Ƿ����ɹ�����
        
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
    
    void MonsterInit();
    
    void monsterInit();//�����ʼ��

    virtual void OriginalPosition(int RoomNumber);//������ɵ��˵�λ�����꣨δ������

    void start(int type, int positionX, int positionY);//����С�ֵ��������ʼλ��

    void MoveMonster(int num);//С���ƶ�����

    CREATE_FUNC(EnemyMonster);

    EnemyMonster* monster[MonsterNumber];

    void  MoveUpdate(float dt);//����С�ֵ��ƶ�

    void  AttackUpdate(float dt);//����С�ֵĹ���

    virtual cocos2d::Animate* createAnimate_move(int MonsterType, int direction, int num);//�����ƶ�����

    cocos2d::Animate* createAnimate_dead(int MonsterType, int direction, int num1, int num2, unsigned int time);//������������
    
    void MonsterResume();

    void isDead();//С������

    bool isFade;

    bool isAllFade;

    void DeadUpdate(float dt);

    bool isAllDead();//�ж�����С���Ƿ�����
  
    void AllMonstersfade();//����С�ִӵ�ͼ����ʧ

    bool inAttack[4];//����С�ֵĹ���״̬

    int AttackTime[4];//����С�ֵĹ������


};
#endif