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
private:
	Sprite* m_sprite;
};
#endif // !_Entity_H__

