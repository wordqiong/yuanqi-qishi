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

#include "BackGroundMusic.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* BackGroundMusic::createScene()
{
    return BackGroundMusic::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BackGroundMusic::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    audio = SimpleAudioEngine::sharedEngine();

    // set the background music and continuously play it.
    audio->playBackgroundMusic("mymusic.mp3", true);
    auto checkbox = ui::CheckBox::create("MusicControl.png",
        "MusicContolSelected.png",
        "MusicContolSelected.png",
        "CheckBoxNode_Normal.png",
        "CheckBoxNode_Disable.png"
    );
    checkbox->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                log("checkbox 2 clicked");
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (audio->isBackgroundMusicPlaying()) {
                    log("pause 1 clicked");
                    audio->stopBackgroundMusic();
                }
                else
                {
                  audio->playBackgroundMusic("mymusic.mp3", true);
                  log("play1 clicked");
                }
                log("checkbox 1 clicked");
                break;
            default:
                break;
        }
        });
    addChild(checkbox);
    checkbox->setPosition(Vec2(400, 585));
    return true;
}


