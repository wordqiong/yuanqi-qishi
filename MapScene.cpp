#include "MapScene.h"
#include "ui\UIButton.h"
#include<cmath>
#include<string>
using namespace std;
using namespace ui;


#define MAP_WALL 203
#define MAP_LOBBY 12254
#define MAP_ROOM 11853

USING_NS_CC;

Scene* MapScene::createScene()
{
    return MapScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void MapScene::addPotion() {
    Potion* potion = Potion::create();
    string load2 = std::to_string(potion->type);
    potion->final_load = potion->load1 + load2 + potion->load3;
    potion->bindSprite(Sprite::create(potion->final_load));

    potion->getSprite()->setPosition(Point(this->hero->getSprite()->getPositionX() + 200, this->hero->getSprite()->getPositionY() + 100));
    this->PotionVector.push_back(potion);
    this->map->addChild(potion);
}

void MapScene::addGun() {
    Gun* fireGun = Gun::create();
    fireGun->bindSprite(Sprite::create("fireGun.png"));
    fireGun->getSprite()->setPosition(Point(100, 0));//��ʱ�ȹ̶�λ��
    fireGun->getSprite()->setAnchorPoint(Point(0.5,0.45));
    fireGun->is_can_be_used = false;//��ֱ�ӱ���
    this->hero->GunOfHero.push_back(fireGun);//�嵽heroǹ����
    map->addChild(fireGun);

    this->GunsVector.push_back(fireGun);
}

void MapScene::flipped(int direction) {
    if (this->hero->GunOfHero.size() == 1) {
        switch (direction) {
        case 1:
            this->hero->GunOfHero[0]->getSprite()->setFlippedY(true);
            break;
        case 2:
            this->hero->GunOfHero[0]->getSprite()->setFlippedY(false);
        }
    }
    if (this->hero->GunOfHero.size() == 2) {
        switch (direction) {
        case 1:
            this->hero->GunOfHero[1]->getSprite()->setFlippedY(true);
            break;
        case 2:
            this->hero->GunOfHero[1]->getSprite()->setFlippedY(false);
        }
    }
}

bool MapScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //�������������ڴ�����
    map = TMXTiledMap::create("map.tmx");
    layer2 = map->getLayer("layer2");
    layer2->setVisible(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (map == nullptr)
    {
        log("tile map not found");
    }
    else
    {
        map->setAnchorPoint(Vec2::ZERO);
        map->setPosition(0, -32 * (100 - 18));
        addChild(map);
    }
    //����hero���������ڵ�ͼ����
    heroInit();

    this->addGun();

    //������ǹ
    Gun* fireGun = Gun::create();
    fireGun->bindSprite(Sprite::create("manyBullet.png"));
    fireGun->getSprite()->setPosition(Point(this->hero->getSprite()->getPositionX() -200, this->hero->getSprite()->getPositionY() -100));//��ʱ�ȹ̶�λ��
    fireGun->getSprite()->setAnchorPoint(Point(0.5, 0.45));
    map->addChild(fireGun);
    this->GunsVector.push_back(fireGun);

    //����ǹ֧    ���ˣ��ڲ���ǹ֧ʱ��Ҫ��������Ҫ������ǹ֧��������������ټ�
    this->GunsVector[0]->getSprite()->setPosition(Point(this->hero->getSprite()->getPositionX()+18 , this->hero->getSprite()->getPositionY() + 17));
   
    this->addPotion();//����Ѫƿ
    

    //��һ��������һ�£�ÿ�β������ʱ��Ҫ����һ�£�����һ����Ĺ���������գ������²�����������is_monster_emptyΪfalse
    Monster* monster = Monster::create();
    monster->bindSprite(Sprite::create("MonsterShooter.png"));
    monster->getSprite()->setPosition(Point(this->hero->getSprite()->getPositionX() + 120, this->hero->getSprite()->getPositionY() + 90));
    map->addChild(monster);
    this->MonsterVector.push_back(monster);
    this->is_monster_empty = false;
    this->num_of_alive_monster = this->MonsterVector.size();

    //��ס��ǹ
    Button* ShootButton = Button::create("ShootButton2.png", "ShootButton.png");
    float x = origin.x + visibleSize.width - ShootButton->getContentSize().width / 2;
    float y = origin.y + ShootButton->getContentSize().height / 2;
    ShootButton->setPosition(Vec2(x,y));
    ShootButton->addTouchEventListener(CC_CALLBACK_2(MapScene::touchCallBack,this));
    this->addChild(ShootButton);
//   // //posted by mxy

    //�źŰ�ť
     signalItem = MenuItemImage::create(
        "signalButton.png",
        "shootButton.png",
        CC_CALLBACK_1(MapScene::menuCloseCallback, this));
    signalItem->setVisible(false);

    if (signalItem == nullptr ||
        signalItem->getContentSize().width <= 0 ||
        signalItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - signalItem->getContentSize().width / 2;
        float y = origin.y + signalItem->getContentSize().height / 2;
        signalItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(signalItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //��ǹ��ť
    changGunItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MapScene::changeGunCallback, this));

    if (changGunItem == nullptr ||
        changGunItem->getContentSize().width <= 0 ||
        changGunItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - changGunItem->getContentSize().width / 2;
        float y = origin.y + changGunItem->getContentSize().height / 2;
        changGunItem->setPosition(Vec2(x, y+150));
    }

    // create menu, it's an autorelease object
    auto menu2 = Menu::create(changGunItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);
    
    scheduleUpdate();
    return true;
}


//�����ť�Ļص�
void MapScene::touchCallBack(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (this->hero->GunOfHero.size() == 1) {
        switch (type)
        {
        case Widget::TouchEventType::BEGAN:
            this->hero->GunOfHero[0]->is_fire = true;
            break;

        case Widget::TouchEventType::MOVED:

            break;

        case Widget::TouchEventType::ENDED:
            this->hero->GunOfHero[0]->is_fire = false;
            break;

        case Widget::TouchEventType::CANCELED:

            break;

        default:
            break;
        }
    }
    if (this->hero->GunOfHero.size() == 2) {
        switch (type)
        {
        case Widget::TouchEventType::BEGAN:
            this->hero->GunOfHero[1]->is_fire = true;
            break;

        case Widget::TouchEventType::MOVED:

            break;

        case Widget::TouchEventType::ENDED:
            this->hero->GunOfHero[1]->is_fire = false;
            break;

        case Widget::TouchEventType::CANCELED:

            break;

        default:
            break;
        }
    }

}

//posted by mxy

void  MapScene::heroInit()
{
    hero = Hero::create();
    hero->bindSprite(Sprite::create("knight.png"));
    direction = 2;//��ʼ��������Ϊ����
    isStand = true;//��ʼ״̬Ϊվ��
    isDirectionChange = false;
    map->addChild(hero);
    hero->getSprite()->setAnchorPoint(Vec2::ZERO);
    hero->getSprite()->setPosition(32 * 10.0f, 32 * 92.0f);//����hero���������ڵ�ͼ����
}

Animate* MapScene::createAnimate(int direction, int num)
{
    auto* m_frameCache = SpriteFrameCache::getInstance();
    m_frameCache->addSpriteFramesWithFile("herorun.plist", "herorun.png");
    Vector<SpriteFrame*>frameArray;
    for (int i = 1; i <= num; i++)
    {
        auto* frame = m_frameCache->getSpriteFrameByName(
            StringUtils::format("%d%d.png", direction, i));
        frameArray.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(frameArray);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);
    return Animate::create(animation);
}

void MapScene::HeroResume()
{
    hero->getSprite()->stopAllActions();
    hero->getSprite()->runAction(createAnimate(this->direction, 1));
}


void MapScene::update(float delta)
{
    Node::update(delta);
    auto leftArrow = EventKeyboard::KeyCode::KEY_A, rightArrow = EventKeyboard::KeyCode::KEY_D,
        upArrow = EventKeyboard::KeyCode::KEY_W, downArrow = EventKeyboard::KeyCode::KEY_S;
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
    float offsetX = 0, offsetY = 0;
    if (keys[leftArrow])
    {
        if (direction == 2)
        {
            isDirectionChange = true;
        }
        direction = 1;//��������
        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = -1.41;
            if (keys[upArrow])
            {
                FinalMove(offsetX, offsetY, 'a', 'd', 'w');
            }
            if (keys[downArrow])
            {
                FinalMove(offsetX, offsetY, 'a', 'd', 's');
            }
        }
        else
        {
            offsetX = -4;
            FinalMove(offsetX, offsetY, 'a', 'd');
        }

    }
    if (keys[rightArrow])
    {
        if (direction == 1)
        {
            isDirectionChange = true;
        }
        direction = 2;//��������
        if (keys[upArrow] || keys[downArrow])
        {
            offsetX = 1.41;
            if (keys[upArrow])
            {
                FinalMove(offsetX, offsetY, 'd', 'a', 'w');
            }
            if (keys[downArrow])
            {
                FinalMove(offsetX, offsetY, 'd', 'a', 's');
            }
        }
        else
        {
            offsetX = 4;
            FinalMove(offsetX, offsetY, 'd', 'a');
        }


    }
    if (keys[upArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = 1.41;
            if (keys[rightArrow])
            {
                FinalMove(offsetX, offsetY, 'w', 's', 'd');
            }
            if (keys[leftArrow])
            {
                FinalMove(offsetX, offsetY, 'w', 's', 'a');
            }
        }
        else
        {
            offsetY = 4;
            FinalMove(offsetX, offsetY, 'w', 's');
        }


    }
    if (keys[downArrow])
    {
        if (keys[rightArrow] || keys[leftArrow])
        {
            offsetY = -1.41;
            if (keys[rightArrow])
            {
                FinalMove(offsetX, offsetY, 's', 'w', 'd');
            }
            if (keys[leftArrow])
            {
                FinalMove(offsetX, offsetY, 's', 'w', 'a');
            }
        }
        else
        {
            offsetY = -4;
            FinalMove(offsetX, offsetY, 's', 'w');
        }

    }
    if (offsetX == 0 && offsetY == 0)
    {
        HeroResume();
        isStand = true;
    }

    //ǹе����
    for (auto gun : this->hero->GunOfHero) {
        gun->getSprite()->setPosition(Point(this->hero->getSprite()->getPositionX() + 45, this->hero->getSprite()->getPositionY() + 17));
    }
    

    //��ǹ��Ŀǰ����map���ǹ�飬�Ȼỻ��hero��ǹ�飩��һ��ǹʱ��0����ǹ��������ǹʱ��1����ǹ
    if (this->hero->GunOfHero.size() == 1) {
        if (!this->hero->GunOfHero[0]->BulletsVector.empty()) {
            for (auto Bullet : this->hero->GunOfHero[0]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() - 5, Bullet->getSprite()->getPositionY() - 5, MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
    }
    if (this->hero->GunOfHero.size() == 2) {
        if (!this->hero->GunOfHero[1]->BulletsVector.empty()) {
            for (auto Bullet : this->hero->GunOfHero[1]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() - 5, Bullet->getSprite()->getPositionY() - 5, MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
        if (!this->hero->GunOfHero[0]->BulletsVector.empty()) {
            for (auto Bullet : this->hero->GunOfHero[0]->BulletsVector) {
                if (!Bullet->isNeedFade) {
                    Bullet->MovebyLine();
                    if (!(MapScene::isCanReach(Bullet->getSprite()->getPositionX() +20 * (Bullet->numx / Bullet->S), Bullet->getSprite()->getPositionY()+ 20 * (Bullet->numy / Bullet->S), MAP_WALL))) {
                        /*this->GunsVector.at(0)->removeChild(Bullet,true);*///+2 * (Bullet->numx / Bullet->S)
                        Bullet->getSprite()->setVisible(false);
                        Bullet->isNeedFade = true;

                    }
                }

            }
        }
    }
    
        //ȷ����ǹ������ת��
    for (auto monster : this->MonsterVector) {
        if (monster->isAlive) {
            if (this->hero->GunOfHero.size() == 1) {
                this->hero->GunOfHero[0]->revolve(this->hero->GunOfHero[0]->bindEnemy(monster));
            }
            else if (this->hero->GunOfHero.size() == 2) {
                this->hero->GunOfHero[1]->revolve(this->hero->GunOfHero[1]->bindEnemy(monster));
            }
        }
    }
       
                

    //�ж�ʲôʱ�򣨼�ǹ����Ѫƿ
    if (!this->PotionVector.empty()) {
        for (auto potion : this->PotionVector) {
            //���û��ʹ�ù�
            if (potion->is_can_be_used) {
                int x = (int)potion->getSprite()->getPositionX()-30 - (int)hero->getSprite()->getPositionX();
                int y = (int)potion->getSprite()->getPositionY()-30 - (int)hero->getSprite()->getPositionY();
                int s_s = x * x + y * y;

                int s = (int)sqrt((float)s_s);

             
                if (s <= 40) {
                    
                    this->BindedPotion = potion;
                    this->is_Bind_Potion = true;
                    this->signalItem->setVisible(true);
                }
                else {
                    this->is_Bind_Potion = false;
                    this->signalItem->setVisible(false);
                }
            }
        }
    }
    
    for (auto gun : this->GunsVector) {
        if (gun->is_can_be_used) {
            int x = (int)gun->getSprite()->getPositionX() - 30 - (int)hero->getSprite()->getPositionX();
            int y = (int)gun->getSprite()->getPositionY() - 30 - (int)hero->getSprite()->getPositionY();
            int s_s = x * x + y * y;

            int s = (int)sqrt((float)s_s);
            /*log("%d", s)*/;
            if (s <= 40) {
                this->BindedGun = gun;
                this->is_Bind_Gun = true;
                this->signalItem->setVisible(true);
            }
            else {
                this->is_Bind_Gun = false;
                if (!this->is_Bind_Potion) {
                    this->signalItem->setVisible(false);
                }
                
            }
        }
    }

    //�ӵ��������ײ

    for (auto monster : this->MonsterVector) {
        if (monster->isAlive) {
            if (this->hero->GunOfHero.size() == 1){
                if (!this->hero->GunOfHero[0]->BulletsVector.empty()) {
                    for (auto Bullet : this->hero->GunOfHero[0]->BulletsVector) {
                        if (!Bullet->isNeedFade) {
                            if (Bullet->is_hit_Monster(monster)) {
                                Bullet->isNeedFade = true;
                                Bullet->getSprite()->setVisible(false);
                                monster->blood -= 3;
                                log("%d", monster->blood);
                            }
                        }
                    }
                }
            }
            if (this->hero->GunOfHero.size() == 2) {
                if (!this->hero->GunOfHero[1]->BulletsVector.empty()) {
                    for (auto Bullet : this->hero->GunOfHero[1]->BulletsVector) {
                        if (!Bullet->isNeedFade) {
                            if (Bullet->is_hit_Monster(monster)) {
                                Bullet->isNeedFade = true;
                                Bullet->getSprite()->setVisible(false);
                                monster->blood -= 3;
                                log("%d", monster->blood);
                            }
                        }
                    }
                }
            }
        }
    }
            
        

    //��������
    for (auto monster : this->MonsterVector) {
        if(monster->isAlive){
            if (monster->blood <= 0) {
                monster->isAlive = false;
                monster->getSprite()->setVisible(false);//���鲻�ɼ�
                this->num_of_alive_monster -= 1;//��Ĺ���������һ
               //�˴� ���ԼӸ���������
                //��ԭλ�ò��� ��һ�Σ� ����
            }
        }
    }
        

    //���������ǹ����󶨵Ĺ���������ķ�������Ϊ��ʼֵ
   
        if (this->num_of_alive_monster == 0) {
            if (this->direction == 1) {
                for (auto gun : this->hero->GunOfHero) {

                    gun->getSprite()->setRotation(180);
                    gun->shootVector = Point(-10, 0);
                }
            }
            if (this->direction == 2) {
                    for (auto gun : this->hero->GunOfHero) {
                    gun->getSprite()->setRotation(0);
                    gun->shootVector = Point(10, 0);
                }
            }
            this->is_monster_empty = true;
        }
    
    


    //ǹ�����ﷴת
    this->flipped(this->direction);

    //ֻ��ʾһ��ǹ
    if (this->hero->GunOfHero.size() == 2) {
        this->hero->GunOfHero[0]->getSprite()->setVisible(false);
        this->hero->GunOfHero[1]->getSprite()->setVisible(true);
    }

    offsetX = offsetY = 0;

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//�źŰ�ť�Ļص�,���жϵ������Ա�ʱ����ʾ�źŰ�ť�����Ͳ�����ɾ��
void MapScene::menuCloseCallback(Ref* pSender)
{
    if (this->is_Bind_Potion) {
        this->BindedPotion->setVisible(false);
        this->BindedPotion->is_can_be_used = false;
        this->is_Bind_Potion = false;
        this->signalItem->setVisible(false);//ҩˮʹ�ú������źŰ�ť
        //��Ѫ����֮��Ӻ���

    }
    if (this->is_Bind_Gun) {
        this->BindedGun->is_can_be_used = false;
        this->hero->addGun(this->BindedGun);//ǹ����hero��ǹ��
        this->is_Bind_Gun = false;
        this->signalItem->setVisible(false);//����ǹ�������źŰ�ť
    }       
}

void MapScene::changeGunCallback(cocos2d::Ref* pSender) {
    if(this->hero->GunOfHero.size()==2){
        vector<Gun*> changeVector;
        changeVector.push_back(this->hero->GunOfHero[0]);
        this->hero->GunOfHero[0] = this->hero->GunOfHero[1];
        this->hero->GunOfHero[1] = changeVector[0];
        
    }

}


bool MapScene::isCanReach(float x, float y, int Type_Wall)
{
    bool result;
    int mapX = (int)((x - 16) / 32 + 1);
    int mapY = (int)(99 - (y - 16) / 32);
    if (mapX < 0 || mapX>73 || mapY < 0 || mapY>99)
    {
        return false;
    }
    int tileGid = layer2->getTileGIDAt(Vec2(mapX, mapY));
    log("e:%d\nY:%d,X:%d", tileGid, mapY, mapX);
    if (tileGid == Type_Wall)
    {
        result = false;//�����ƶ�
    }
    else
    {
        result = true;//���ƶ�
    }
    return result;
}

void MapScene::PureMapMove(float offsetX, float offsetY)
{
    auto* animate = createAnimate(direction, 3);
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(map->getPositionX() - offsetX, map->getPositionY() - offsetY));
    if (isStand == true || isDirectionChange == true)
    {
        HeroResume();
        hero->getSprite()->runAction(animate);
        isStand = false;
        isDirectionChange = false;
    }
    map->runAction(moveTo);
}
void MapScene::PureHeroMove(float offsetX, float offsetY)
{
    auto moveTo = MoveTo::create(1.0 / 1000, Vec2(hero->getSprite()->getPositionX() + offsetX, hero->getSprite()->getPositionY() + offsetY));
    hero->getSprite()->runAction(moveTo);
}
void MapScene::AllMove(float offsetX, float offsetY)
{
    PureMapMove(offsetX, offsetY);
    PureHeroMove(offsetX, offsetY);
}

bool MapScene::JudgeWall(float offsetX, float offsetY, char key_arrow)
{
    int i = 1;
    while (i <= 8)
    {
        if (!isCanReach(hero->getSprite()->getPositionX() + offsetX + ('d' == key_arrow) * (1) * (i * 32) + ('a' == key_arrow) * (-1) * (i * 32),
            hero->getSprite()->getPositionY() + offsetY + ('w' == key_arrow) * (1) * (i * 32) + ('s' == key_arrow) * (-1) * (i * 32), MAP_WALL))
        {

            /* log("i=%d", i);*/
            break;
        }
        else
            i++;

    }

    if (i <= 5)
        return true;//���Χ����ǽ
    else
        return false;
}


void MapScene::FinalMove(float offsetX, float offsetY, char key_arrow_1, char key_arrow_2, char key_arrow_3)
{
    if (((JudgeWall(offsetX, offsetY, key_arrow_1)
        && isCanReach(hero->getSprite()->getPositionX() + offsetX, hero->getSprite()->getPositionY() + offsetY, MAP_WALL))
        || ((JudgeWall(offsetX, offsetY, key_arrow_2)
            && isCanReach(hero->getSprite()->getPositionX() + offsetX, hero->getSprite()->getPositionY() + offsetY, MAP_WALL))))
        && isCanReach(hero->getSprite()->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getSprite()->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
    {
        if (key_arrow_3 != '-')
        {
            if (isCanReach(hero->getSprite()->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getSprite()->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
            {
                PureHeroMove(offsetX, offsetY);
            }
        }
        else
        {
            PureHeroMove(offsetX, offsetY);
        }
    }
    else
    {
        if (isCanReach(hero->getSprite()->getPositionX() + offsetX + ('d' == key_arrow_1) * (1 * 16) + ('a' == key_arrow_1) * (-1 * 16), hero->getSprite()->getPositionY() + offsetY + ('w' == key_arrow_1) * (1 * 16) + ('s' == key_arrow_1) * (-1 * 16), MAP_WALL))
        {
            if (key_arrow_3 != '-')
            {
                if (isCanReach(hero->getSprite()->getPositionX() + offsetX + ('d' == key_arrow_3) * (1 * 16) + ('a' == key_arrow_3) * (-1 * 16), hero->getSprite()->getPositionY() + offsetY + ('w' == key_arrow_3) * (1 * 16) + ('s' == key_arrow_3) * (-1 * 16), MAP_WALL))
                {
                    AllMove(offsetX, offsetY);
                }
            }
            else
            {
                AllMove(offsetX, offsetY);
            }
        }
    }
}

//void MapScene::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    this->GunsVector.at(0)->Fire();//�����������createBullets���ƶ��������Ժ��ٸ�
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//}


//void MapScene::OpenDoor()
//{
//    if (StateDoor())
//    {
//        //������ӵ��Ǽ�������ǽ��
//    }
//
//}
//void MapScene::CloseDoor()
//{
//    if (!StateDoor())
//    {
//        //������·�����ǽ��
//    }
//}
//bool MapScene::StateDoor()
//{
//    //�ƻ�Ŀ�� ��ȥ��ǰ
//    //true ���� �������� ����
//    //false �������߽�����
//    if (PositionDoor)
//    {
//        if (!isCanReach(32 * (10 - x), 32 * (92 - y), MAP_LOBBY))
//        {
//            PositionDoor = false;
//            return true;
//        }
//    }
//    else
//    {
//        if (!isCanReach(32 * (10 - x), 32 * (92 - y), MAP_ROOM))
//        {
//            PositionDoor = true;
//            return false;
//        }
//    }
//}