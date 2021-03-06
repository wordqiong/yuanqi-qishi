/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class BackGroundMusic : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
   cocos2d::ui::LoadingBar* loadingBar;
    virtual bool init();
    CocosDenshion::SimpleAudioEngine* audio;
    cocos2d::ui::CheckBox checkbox;
    // implement the "static create()" method manually
    CREATE_FUNC(BackGroundMusic);
private:
    float ChangeValumn = 0;
 
   
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    void BackGroundMusic::setValumn(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
