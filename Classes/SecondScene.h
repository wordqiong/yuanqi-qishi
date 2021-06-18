#ifndef __SecondScene_H__
#define __SecondScene_H__
#include "cocos2d.h"

using namespace cocos2d;
class SecondScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	void button(MenuItemImage* button, const char* name);
	void menuInitialBackCallback(cocos2d::Ref* pSender);
	void SecondScene::menuStartGameCallback(Ref* pSender);
	CREATE_FUNC(SecondScene);
};
#endif 

