#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
#include"Gun.h"
#include "Bullet.h"
#include"ui/UIWidget.h"
#include "Potion.h"





class MapScene : public cocos2d::Scene
{
public:


    static MapScene* sharedScene;//创建指向该场景的指针

    int direction;//获取人物移动的方向

    bool isStand;//判断人物是否站立不动

    bool isDirectionChange;//判断人物移动方向是否变化

    void heroInit();//人物初始化

    void touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type);//按钮监听
    void menuCloseCallback(cocos2d::Ref* pSender);//信号按钮监听

    void flipped(int direction);//把枪反转



    void addPotion();

    static cocos2d::Scene* createScene();

    virtual bool init();
    //测试用的成员
   //瓦片初始地图
    cocos2d::TMXTiledMap* map;
    //障碍物所在图层
    cocos2d::TMXLayer* layer2;
    //hero单位
    cocos2d::Sprite* hero;
    //移动所需的语句
    void update(float delta) override;

        void addGun();
    vector<Gun*> GunsVector;//枪械容器
    vector<Monster*> MonsterVector;
    vector<Potion*> PotionVector;
    Potion* BindedPotion;
    MenuItemImage* signalItem;//信号按钮

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
    int x = 0, y = 0;//起点
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
    //自用
    void MapScene::AllMove(float offsetX, float offsetY);
    void MapScene::PureMapMove(float offsetX, float offsetY);
    void MapScene::PureHeroMove(float offsetX, float offsetY);
    bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow);

    void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
    int MonsterNum;
    bool PositionDoor = true;//in room ->ture in lobby->false 
};
#endif 
