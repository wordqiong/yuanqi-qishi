#ifndef __SafeRoomMove_H__
#define __SafeRoomMove_H__
#include "cocos2d.h"

using namespace cocos2d;
class SafeRoomMove : public Scene
{
public:

	static SafeRoomMove* sharedScene;//创建指向该场景的指针

	int direction;//获取人物移动的方向

	bool isStand;//判断人物是否站立不动

	bool isDirectionChange;//判断人物移动方向是否变化

	void heroInit();//人物初始化

	static Scene* createScene();

	virtual bool init();
	//瓦片初始地图
	TMXTiledMap* SafeMap;
	//障碍物所在图层
	TMXLayer* barrier;
	//hero单位
	Sprite* hero;
	void menuSafeMoveRoomCallback(cocos2d::Ref* pSender);


	cocos2d::Animate* createAnimate(int direction, int num);

	void HeroResume();
	//移动所需的语句
	void update(float delta) override;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	/*
   *@brief  Judge next movement whether or not barrier
   *@author wyh
   */
	bool SafeRoomMove::isCanReach(float x, float y, int Type_Wall, bool diliver = false);
	CREATE_FUNC(SafeRoomMove);
protected:
	//自用
	void SafeRoomMove::AllMove(float offsetX, float offsetY);
	void SafeRoomMove::PureMapMove(float offsetX, float offsetY);
	void SafeRoomMove::PureHeroMove(float offsetX, float offsetY);
	bool SafeRoomMove::JudgeWall(float offsetX, float offsetY, char key_arrow);
	bool WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3);
	void SafeRoomMove::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
	bool SafeRoomMove::JudgeBarrier(float offsetX, float offsetY, char key_arrow);
};
#endif 