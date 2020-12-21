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

#include "Room1.h"
#include "Definitions.h"
#include "PauseScene.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"

float f_time = 21600.f;

USING_NS_CC;

Scene* Room1::createScene()
{
    return Room1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Room1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    /////////////////////////////
    // 4. all elements in room

    // background 
    auto background1 = Sprite::create(s_r1back1);
    background1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.715);
    this->addChild(background1);

    // suspect back
    auto susp1 = Sprite::create(s_r1susp1);
    susp1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(susp1);

    // suspect top
    auto susp2 = Sprite::create(s_r1susp2);
    susp2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(susp2);

    // table
    auto table = Sprite::create(s_r1table);
    table->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3);
    this->addChild(table);

    // nearest part of room
    auto layer1 = new (std::nothrow) MainScene();
    auto layer = LayerMultiplex::create(layer1, nullptr);
    addChild(layer, 0);
    layer1->release();

    /////////////////////////////
    // 5. menu

    // play
    auto play = MenuItemImage::create(s_play, s_play, CC_CALLBACK_1(Room1::PauseScene, this));
    play->setPosition(origin.x + visibleSize.width / 23.8, origin.y + visibleSize.height / 1.078);

    // pause
    auto pause = MenuItemImage::create(s_pause, s_pause, CC_CALLBACK_1(Room1::PauseScene, this));
    pause->setPosition(origin.x + visibleSize.width / 16.4, origin.y + visibleSize.height / 1.078);

    // record
    auto record = MenuItemImage::create(s_record, s_record, CC_CALLBACK_1(Room1::PauseScene, this));
    record->setPosition(origin.x + visibleSize.width / 12.3, origin.y + visibleSize.height / 1.078);

    // stop
    auto stop = MenuItemImage::create(s_stop, s_stop, CC_CALLBACK_1(Room1::PauseScene, this));
    stop->setPosition(origin.x + visibleSize.width / 9.85, origin.y + visibleSize.height / 1.078);

    // menu
    auto menu = Menu::create(play, pause, record,stop, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);

    /////////////////////////////
    // 6. lr parallax

    // left block button
    auto leftblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room1::GoToRoom2, this));
    leftblock->setPosition(origin.x , origin.y + visibleSize.height/2);

    // right block button
    auto rightblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room1::GoToRoom4, this));
    rightblock->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height / 2);
 
    // top block button
    auto topblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room1::GoToRoom3, this));
    topblock->setPosition(origin.x + visibleSize.width/2, origin.y+visibleSize.height);

    // lr buttons
    auto menulr = Menu::create(leftblock, rightblock, topblock, NULL);
    menulr->setPosition(Point::ZERO);
    this->addChild(menulr);
  
    // move to lr
    auto mouseListenerSlide = EventListenerMouse::create();
    mouseListenerSlide->onMouseMove = [=](EventMouse* event) 
    {
        Point mousePosition = Point(event->getCursorX(), event->getCursorY());
        auto moveByLayer = MoveBy::create(2, Vec2(32, 0));
        auto moveByBack = MoveBy::create(2, Vec2(35.5, 0));
        auto moveBySusp1 = MoveBy::create(2, Vec2(15.5, 0));
        auto moveBySusp2 = MoveBy::create(2, Vec2(25.5, 0));
        auto moveByTable = MoveBy::create(2, Vec2(25.5, 0));
        auto moveByUpLayer = MoveBy::create(2, Vec2(0, 50));
        auto moveByUpBack = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpSusp1 = MoveBy::create(2, Vec2(0, 15));
        auto moveByUpSusp2 = MoveBy::create(2, Vec2(0, 25));
        auto moveByUpTable = MoveBy::create(2, Vec2(0, 25));
        if (leftblock->getBoundingBox().containsPoint(mousePosition) && flagL == false) 
        {
            layer1->runAction(moveByLayer);
            background1->runAction(moveByBack);
            susp1->runAction(moveBySusp1);
            susp2->runAction(moveBySusp2);
            table->runAction(moveByTable);
            flagL = true;
        }
        if (leftblock->getBoundingBox().containsPoint(mousePosition) != true && flagL == true) 
        {
            layer1->runAction(moveByLayer->reverse());
            background1->runAction(moveByBack->reverse());
            susp1->runAction(moveBySusp1->reverse());
            susp2->runAction(moveBySusp2->reverse());
            table->runAction(moveByTable->reverse());
            flagL = false;
        }
        if (rightblock->getBoundingBox().containsPoint(mousePosition) && flagR == false) 
        {
            layer1->runAction(moveByLayer->reverse());
            background1->runAction(moveByBack->reverse());
            susp1->runAction(moveBySusp1->reverse());
            susp2->runAction(moveBySusp2->reverse());
            table->runAction(moveByTable->reverse());
            flagR = true;
        }
        if (rightblock->getBoundingBox().containsPoint(mousePosition) != true && flagR == true) 
        {
            layer1->runAction(moveByLayer);
            background1->runAction(moveByBack);
            susp1->runAction(moveBySusp1);
            susp2->runAction(moveBySusp2);
            table->runAction(moveByTable);
            flagR = false;
        }
        if (topblock->getBoundingBox().containsPoint(mousePosition) && flagT == false)
        {
            layer1->runAction(moveByUpLayer->reverse());
            background1->runAction(moveByUpBack->reverse());
            susp1->runAction(moveByUpSusp1->reverse());
            susp2->runAction(moveByUpSusp2->reverse());
            table->runAction(moveByUpTable->reverse());

            flagT = true;
        }
        if (topblock->getBoundingBox().containsPoint(mousePosition) != true && flagT == true)
        {
            layer1->runAction(moveByUpLayer);
            background1->runAction(moveByUpBack);
            susp1->runAction(moveByUpSusp1);
            susp2->runAction(moveByUpSusp2);
            table->runAction(moveByUpTable);
            flagT = false;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListenerSlide, this);
    
    /////////////////////////////
    // 7. clock

    // clock
    clocktime = Label::createWithTTF("", f_font, 16);
    clocktime->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.059);
    clocktime->setColor(Color3B::Color3B(195, 163, 138));
    this->addChild(clocktime);
    this->schedule(CC_SCHEDULE_SELECTOR(Room1::UpdateTimer, f_time));

    return true;
}
void Room1::GoToRoom2(cocos2d::Ref* sender)
{
    auto scene = Room2::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(TRANSITION_TIME, scene));
}
void Room1::GoToRoom3(cocos2d::Ref* sender)
{
    auto scene = Room3::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(TRANSITION_TIME, scene));
}
void Room1::GoToRoom4(cocos2d::Ref* sender)
{
    auto scene = Room4::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITION_TIME, scene));
}
MainScene::~MainScene()
{
}
MainScene::MainScene()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // background top
    auto background2 = Sprite::create(s_r1back2);
    background2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(background2);

    // coat
    // later should add button to end day
    auto coat = Sprite::create(s_r1coat);
    coat->setPosition(origin.x + visibleSize.width / 1.07, origin.y + visibleSize.height / 1.63);
    this->addChild(coat);
    
    // left detective
    auto detective1 = Sprite::create(s_r1det1);
    detective1->setPosition(origin.x + visibleSize.width / 6.53, origin.y + visibleSize.height / 2);
    this->addChild(detective1);

    // right detective
    auto detective2 = Sprite::create(s_r1det2);
    detective2->setPosition(origin.x + visibleSize.width / 2.5, origin.y + visibleSize.height / 2);
    this->addChild(detective2);

    // dialog
    auto dialog = Label::createWithTTF("- What do you think of him?\n- He looks like to be a nice guy\n- but i have a strange feeling about him\n- me too", f_font, 16);
    dialog->setPosition(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 5.8);
    dialog->setTextColor(Color4B::Color4B(195, 163, 138, 255));
    dialog->setLineSpacing(-4);
    this->addChild(dialog);
}
void Room1::UpdateTimer(float dt)
{   
    dt = 0.5f;
    f_time += dt;
    int timer = ceil(f_time);
    auto hh = timer / 3600;
    auto mm = (timer % 3600)/60;
    if (mm < 10 && hh < 10) 
    {
        clocktime->setString("0" + std::to_string(hh) + ":0" + std::to_string(mm));
    }
    else if (mm<10)
    {
        clocktime->setString(std::to_string(hh) + ":0" + std::to_string(mm));
    }
    else if (hh<10) 
    {
        clocktime-> setString("0" + std::to_string(hh) + ":" + std::to_string(mm));
    }
    else 
    {
        clocktime->setString(std::to_string(hh)+":"+std::to_string(mm));
    }
}
void Room1::PauseScene(cocos2d::Ref* sender)
{
    auto currentScene = Director::getInstance()->getRunningScene();
    auto scene = PauseScene::createScene();
    auto winSize = Director::getInstance()->getWinSize();
    auto rt = RenderTexture::create(winSize.width, winSize.height);
    rt->getSprite()->setPosition(currentScene->getContentSize().width / 2, currentScene->getContentSize().height / 2);
    rt->begin();
    currentScene->visit();
    rt->end();
    scene->addChild(rt);
    Director::getInstance()->pushScene(scene);
}