#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
class MapScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //�����õĳ�Ա
   //��Ƭ��ʼ��ͼ
    cocos2d::TMXTiledMap* map;
    //�ϰ�������ͼ��
    cocos2d::TMXLayer* layer2;
    //hero��λ
    cocos2d::Sprite* hero;
    //�ƶ���������
    void update(float delta) override;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    CREATE_FUNC(MapScene);
    /*
    *@brief  open doors
	*@author wyh
    */
    void OpenDoor(){}
    /*
   *@brief  close doors
   *@author wyh
   */
    void CloseDoor(){}
    /*
   *@brief  create Mosters
   *@author wyh
   */
    void MosterCreate(){}
    /*
    *@brief  Map move
    *@author wyh
    */
    int x = 0, y = 0;//���
    /*
    *@brief  Judge next movement whether or not barrier
    *@author wyh
    */
    bool MapScene::isCanReach(float x, float y, int Type_Wall);
    /*
    *@brief  Judge the state of door
    *@author wyh
    * @return ture Door
    */
    bool StateDoor();
protected:
    //����
    void MapScene::AllMove(int offsetX, int offsetY);
    void MapScene::PureMapMove(int offsetX, int offsetY);
    void MapScene::PureHeroMove(int offsetX, int offsetY);
    bool MapScene::JudgeWall(int offsetX, int offsetY, char key_arrow);
    bool MapScene::JudgeWall(int offsetX, int offsetY, char key_arrow_1, char key_arrow_2);
    void MapScene::FinalMove(int offsetX, int offsetY, char key_arrow_1, char key_arrow_2 , char key_arrow_3='-');
    int MonsterNum;
    bool PositionDoor = true;//in room ->ture in lobby->false 
};
#endif 
