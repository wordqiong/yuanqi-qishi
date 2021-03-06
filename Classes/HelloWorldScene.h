#ifndef __HELLOWORLDSCENE_H__
#define __HELLOWORLDSCENE_H__

#include "cocos2d.h"
#include "BackGroundMusic.h"

class HelloWorld : public cocos2d::Scene
{
public:
    

    static HelloWorld* helloworld;
    static cocos2d::Scene* createScene();

    virtual bool init();
    BackGroundMusic* BackMusic;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
