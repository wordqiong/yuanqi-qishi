#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__
#include "Enemy.h"
#include "Hero.h"
#include "cocos2d.h"
class Hero;
class MapScene : public cocos2d::Scene
{
public:


    static MapScene* sharedScene;//创建指向该场景的指针

    static cocos2d::Scene* createScene();

    virtual bool init();
    //测试用的成员
   //瓦片初始地图
    cocos2d::TMXTiledMap* map;
    //障碍物所在图层
    cocos2d::TMXLayer* layer2;
    //hero单位
    Hero* Hero;

    //Monster
    EnemyMonster* monster;
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
    void MosterCreate();
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
    void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3 = '-');
protected:
    //自用
    void MapScene::AllMove(float offsetX, float offsetY);
    void MapScene::PureMapMove(float offsetX, float offsetY);
    void MapScene::PureHeroMove(float offsetX, float offsetY);
    bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow, int ValueWall);
    bool MapScene::WhetherHeroMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ValueWall);
   
    bool MapScene::JudgeBarrier(float offsetX, float offsetY, char key_arrow);
    int MonsterNum;
    bool PositionDoor = true;//in room ->ture in lobby->false 

    void MapScene::RoomIn(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3, int ROOM_NUM);


    int MapScene::NumJudgeWhichRoom(int ValueRoom);


    bool MapScene::StateDoor(int ValueWall);
    int JudgeOpenTime = 0;
    int MapScene::JudgeWhichRoomIn();
private:
    int Room[4] = {1};//1表示未曾进入 0表示已经进入
    void MapScene::BloodCreate();
    float MapScene::TransPencent(int type);
    void MapScene::MpCreate();
    void MapScene::AcCreate();
    void  MapScene::BoardCreate();
};
#endif 
