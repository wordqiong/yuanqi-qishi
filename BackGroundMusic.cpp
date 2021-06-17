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


    loadingBar = ui::LoadingBar::create("blood.png", 100);
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);

    loadingBar->setScale(0.3f);
    this->addChild(loadingBar);
    loadingBar->setPosition(Vec2(400, 620));

    auto label = Label::createWithTTF("press '8'(up)or'2'(down) to control volume", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(400, 620));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

  

    checkbox->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {  
     
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                log("checkbox 2 clicked");
               
                break;
            case ui::Widget::TouchEventType::ENDED:

                if (audio->isBackgroundMusicPlaying()) {
                    log("pause 1 clicked");
                    unschedule(CC_SCHEDULE_SELECTOR(BackGroundMusic::setValumn));
                    audio->stopBackgroundMusic();
                }
                else
                {
                  
                  /*  loadingBar->setVisible(true);*/
                    // set the direction of the loading bars progress
                    schedule(CC_SCHEDULE_SELECTOR(BackGroundMusic::setValumn));
                  audio->playBackgroundMusic("mymusic.mp3", true);
                  log("play1 clicked");
                }
                log("checkbox 1 clicked");
                break;
            default:
                break;
        }
        });
    this->addChild(checkbox);
    checkbox->setPosition(Vec2(400, 585));

      
    return true;
}
void BackGroundMusic::setValumn(float dt)
{
    


    if (audio->isBackgroundMusicPlaying())
    {
        auto 
            upArrow = EventKeyboard::KeyCode::KEY_8, downArrow = EventKeyboard::KeyCode::KEY_2;
        auto listener = EventListenerKeyboard::create();
        listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            keys[keyCode] = true;

            /* log("%d", keyCode);*/
        };

        listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            keys[keyCode] = false;

        };

        if (keys[upArrow])
        {
            if(ChangeValumn>=0)
            ChangeValumn--;

            log("upupupup");
        }
        if (keys[downArrow])
        {
            if (ChangeValumn <= 100)
            {
                ChangeValumn++;
            }


        }
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    }
    log("%f",1.0 - ChangeValumn / 100);

    loadingBar->setPercent(audio->getBackgroundMusicVolume() * 100);
    audio->setBackgroundMusicVolume(1.0 - ChangeValumn / 100);
}


