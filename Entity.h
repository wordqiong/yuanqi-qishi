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
private:
	Sprite* m_sprite;
};
#endif // !_Entity_H__

