#ifndef _Entity_H__
#define _Entity_H__
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node {
public:
	Entity();
	~Entity();
	Sprite* getSprite();//获取精灵
	void bindSprite(Sprite* sprite);//绑定
	//bool is_can_be_used = true;//药水和武器用得到
	//int Type_of_Binded_Item = 1 ;//1为药水，2为枪
	//virtual void revolve(float degree);
	//virtual float bindEnemy(Monster* monster1);
private:
	Sprite* m_sprite;
};
#endif // !_Entity_H__

