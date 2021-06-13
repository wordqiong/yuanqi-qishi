#ifndef __SafeRoomMove_H__
#define __SafeRoomMove_H__
#include "cocos2d.h"

using namespace cocos2d;
class SafeRoomMove : public Scene
{
public:

	static SafeRoomMove* sharedScene;//����ָ��ó�����ָ��

	int direction;//��ȡ�����ƶ��ķ���

	bool isStand;//�ж������Ƿ�վ������

	bool isDirectionChange;//�ж������ƶ������Ƿ�仯

	void heroInit();//�����ʼ��

	static Scene* createScene();

	virtual bool init();
	//��Ƭ��ʼ��ͼ
	TMXTiledMap* SafeMap;
	//�ϰ�������ͼ��
	TMXLayer* barrier;
	//hero��λ
	Sprite* hero;
	void menuSafeMoveRoomCallback(cocos2d::Ref* pSender);


	cocos2d::Animate* createAnimate(int direction, int num);

	void HeroResume();
	//�ƶ���������
	void update(float delta) override;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	/*
   *@brief  Judge next movement whether or not barrier
   *@author wyh
   */
	bool SafeRoomMove::isCanReach(float x, float y, int Type_Wall, bool diliver = false);
	CREATE_FUNC(SafeRoomMove);
protected:
	//����
	void SafeRoomMove::AllMove(float offsetX, float offsetY);
	void SafeRoomMove::PureMapMove(float offsetX, float offsetY);
	void SafeRoomMove::PureHeroMove(float offsetX, float offsetY);
	bool SafeRoomMove::JudgeWall(float offsetX, float offsetY, char key_arrow);
	bool WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3);
	void SafeRoomMove::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
	bool SafeRoomMove::JudgeBarrier(float offsetX, float offsetY, char key_arrow);
};
#endif 