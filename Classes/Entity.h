#ifndef _Entity_H__
#define _Entity_H__
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node {
public:
	Entity();
	~Entity();
	Sprite* getSprite();//��ȡ����
	void bindSprite(Sprite* sprite);//��
	//bool is_can_be_used = true;//ҩˮ�������õõ�
	//int Type_of_Binded_Item = 1 ;//1Ϊҩˮ��2Ϊǹ
	//virtual void revolve(float degree);
	//virtual float bindEnemy(Monster* monster1);
private:
	Sprite* m_sprite;
};
#endif // !_Entity_H__

