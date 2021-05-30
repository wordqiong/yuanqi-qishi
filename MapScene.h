#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"

class MapScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //测试用的成员
    cocos2d::Size size;
    cocos2d::Sprite* sprite;
    cocos2d::TMXTiledMap* map;


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
    void MapMove();
    int x = 0, y = 0;//起点


};

#endif 
