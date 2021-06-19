#include "AnimationUtil.h"


Animation* AnimationUtil::createAnimWithSingleFrameN(const char* name, float delay, unsigned int iLoops) {
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    Vector<SpriteFrame*>frameArray;

    SpriteFrame* frame = NULL;
    int index = 1;
    do {
        frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, index++));

        /* 不断地获取SpriteFrame对象，直到获取的值为NULL */
        if (frame == NULL) {
            break;
        }
        frameArray.pushBack(frame);
       
    } while (true);

    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);

    return animation;
}

Animation* AnimationUtil::createAnimWithFrameNameAndNum(const char* name, int iNum, float delay, unsigned int iLoops) {
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    Vector<SpriteFrame*>frameArray;

    SpriteFrame* frame = NULL;
    int index = 1;
    for (int i = 1; i <= iNum; i++) {
        frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, i));

        if (frame == NULL) {
            break;
        }

        frameArray.pushBack(frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);

    return animation;
}