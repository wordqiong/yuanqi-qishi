#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_BARRIER_TREE 1456
#define MAP_ROOM_1 11652
#define MAP_ROOM_2 11246
#define MAP_ROOM_3 11853
#define MAP_ROOM_4 11854
#define MAP_DOOR 1217


#include"Hero.h"
#include "cocos2d.h"
#include "Bullet.h"
#include"ui/UIWidget.h"
#include"Potion.h"
#include"Gun.h"
#include "ui/CocosGUI.h"
#include "AnimationUtil.h"
#include "BackGroundMusic.h"
#include"box.h"
#include"Boss.h"



#include "ui\UIButton.h"
#include<cmath>
#include<string>



class Hero;
class Boss;
class Box;
class EnemyMonster;
class MapScene : public cocos2d::Scene
{
public:


    Animation* animation_bullet;


    static MapScene* sharedScene;//����ָ��ó�����ָ��d

    static cocos2d::Scene* createScene();

    bool isMonsterCreated[5];

    void CreateUpdate(float dt);

    void GunUpdate(float dt);



    void touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//��ť����
    
    void menuCloseCallback(cocos2d::Ref* pSender);//�źŰ�ť����
   
    void changeGunCallback(cocos2d::Ref* pSender);//�źŰ�ť����

    void flipped(int direction);//��ǹ��ת

    void addPotion();

    void addGun();

    vector<Gun*> GunsVector;//ǹе����
    Vector<Bullet*> MonsterBulletsVector;
    /*vector<Monster*> MonsterVector;*/
    vector<Potion*> PotionVector;
    Potion* BindedPotion;//��Ϣ��ť�󶨵���Ʒ
    Gun* BindedGun;
    bool is_Bind_Potion = false;
    bool is_Bind_Gun = false;
    MenuItemImage* signalItem;//�źŰ�ť
    MenuItemImage* changGunItem;//��ǹ��ť
    void addShootButton();//��ʼ�������ť
    void addsignalItem();//��ʼ���źŰ�ť
    void addchangGunItem();//��ʼ����ǹ��ť
    //hero��λ
    Hero* Hero;

    EnemyMonster* monster;

    Box* _box[5];

    bool box_judge[5] = { 0,0,0,0,0 };

    Boss* boss;//����ʵ��
    //�ƶ���������
    
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

    virtual bool init();
    //�����õĳ�Ա
   //��Ƭ��ʼ��ͼ
    cocos2d::TMXTiledMap* map;
    //�ϰ�������ͼ��
    cocos2d::TMXLayer* layer2;
    CREATE_FUNC(MapScene);
    /*
    *@brief  open doors
    *@author wyh
    */
    void OpenDoor();
        /*
       *@brief  close doors
       *@author wyh
       */
        void CloseDoor();
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

    void MapScene::BloodCreate();
    float MapScene::TransPencent(int type);
    void MapScene::MpCreate();
    void MapScene::AcCreate();




    void  MapScene::BoardCreate();
    void  MapScene::Boardupdate();
    //��������ͼ��
    cocos2d::TMXLayer* box_create;
    //������
    cocos2d::TMXLayer* delivery_create;
    bool MapScene::isDelivery(float x, float y);
    void MapScene::RunDelivery(float x, float y);
    void MapScene::DeliveryPlist();
    bool MapScene::init_2();


    bool MapScene::isCanReach(float x, float y, char name = ' ');
    bool MapScene::JudgeBarrier(float offsetX, float offsetY, char key_arrow);

    bool MapScene::isCanReachBoxJudge(float x, float y, char name = ' ');

    void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
protected:
    //����
    void MapScene::AllMove(float offsetX, float offsetY);
    void MapScene::PureMapMove(float offsetX, float offsetY);
    void MapScene::PureHeroMove(float offsetX, float offsetY);
    bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow, int ValueWall);
    bool MapScene::WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ValueWall);

   
    int MonsterNum;
    bool PositionDoor = true;//in room ->ture in lobby->false 

    void MapScene::RoomIn(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ROOM_NUM);


    int MapScene::NumJudgeWhichRoom(int ValueRoom);


    bool MapScene::StateDoor(int ValueWall);
    int JudgeOpenTime = 0;
    int MapScene::JudgeWhichRoomIn();



 
private:
    int Room[4] = { 1 ,1,1,1};//1��ʾδ������ 0��ʾ�Ѿ�����

    ui::LoadingBar* BloodLoadingBar;
    ui::LoadingBar* MpLoadingBar;
    ui::LoadingBar* AcLoadingBar;

    //open
    Sprite* runSp[7];
    //close
    Sprite* runSp_2[7];


    Label* BloodLabel;
    Label* AcLabel;
    Label* MPLabel;
    //��Ѫ����
    Label* BloodDelete;
    string BloodNum;
    string MPNum;
    string AcNum;
};
#endif 
