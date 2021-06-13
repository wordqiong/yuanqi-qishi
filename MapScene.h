#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
#include"Gun.h"
#include "Bullet.h"
#include"ui/UIWidget.h"


//class MapScene : public cocos2d::Scene
//{
//public:
//    static cocos2d::Scene* createScene();
//
//    virtual bool init();
//    int direction;//��ȡ�����ƶ��ķ���
//
//    bool isStand;//�ж������Ƿ�վ������
//
//    bool isDirectionChange;//�ж������ƶ������Ƿ�仯
//    void heroInit();
//
//     void touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//��ť����
//    /*void menuCloseCallback(cocos2d::Ref* pSender);*/
//    //�����õĳ�Ա
//   //��Ƭ��ʼ��ͼ
//    cocos2d::TMXTiledMap* map;
//    //�ϰ�������ͼ��
//    cocos2d::TMXLayer* layer2;
//    //hero��λ
//    cocos2d::Sprite* hero;
//    //�ƶ���������
//    void update(float delta) override;
//    void addGun();
//    vector<Gun*> GunsVector;//ǹе����
//    vector<Monster*> MonsterVector;
//    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
//    CREATE_FUNC(MapScene);
//    /*
//    *@brief  open doors
//    *@author wyh
//    */
//    void OpenDoor() {}
//    /*
//   *@brief  close doors
//   *@author wyh
//   */
//    void CloseDoor() {}
//    /*
//   *@brief  create Mosters
//   *@author wyh
//   */
//    void MosterCreate() {}
//    /*
//    *@brief  Map move
//    *@author wyh
//    */
//    int x = 0, y = 0;//���
//    /*
//    *@brief  Judge next movement whether or not barrier
//    *@author wyh
//    */
//    bool MapScene::isCanReach(float x, float y, int Type_Wall);
//    /*
//    *@brief  Judge the state of door
//    *@author wyh
//    * @return ture Door
//    */
//    bool StateDoor();
//
//    cocos2d::Animate* createAnimate(int direction, int num);
//
//    void HeroResume();
//protected:
//    //����
//    void MapScene::AllMove(float offsetX, float offsetY);
//    void MapScene::PureMapMove(float offsetX, float offsetY);
//    void MapScene::PureHeroMove(float offsetX, float offsetY);
//    bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow);
//    void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
//    int MonsterNum;
//    bool PositionDoor = true;//in room ->ture in lobby->false 
//};
//#endif 


class MapScene : public cocos2d::Scene
{
public:


    static MapScene* sharedScene;//����ָ��ó�����ָ��

    int direction;//��ȡ�����ƶ��ķ���

    bool isStand;//�ж������Ƿ�վ������

    bool isDirectionChange;//�ж������ƶ������Ƿ�仯

    void heroInit();//�����ʼ��

    void touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//��ť����

    void flipped(int direction);//��ǹ��ת

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

        void addGun();
    vector<Gun*> GunsVector;//ǹе����
    vector<Monster*> MonsterVector;

    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    CREATE_FUNC(MapScene);
    /*
    *@brief  open doors
    *@author wyh
    */
    void OpenDoor() {}
    /*
   *@brief  close doors
   *@author wyh
   */
    void CloseDoor() {}
    /*
   *@brief  create Mosters
   *@author wyh
   */
    void MosterCreate() {}
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


    cocos2d::Animate* createAnimate(int direction, int num);

    void HeroResume();
protected:
    //����
    void MapScene::AllMove(float offsetX, float offsetY);
    void MapScene::PureMapMove(float offsetX, float offsetY);
    void MapScene::PureHeroMove(float offsetX, float offsetY);
    bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow);

    void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
    int MonsterNum;
    bool PositionDoor = true;//in room ->ture in lobby->false 
};
#endif 