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

#include "Room4.h"
#include "Definitions.h"
#include "PauseScene.h"
#include "Room1.h"
#include "NewDay.h"


USING_NS_CC;

Scene* Room4::createScene()
{
    return Room4::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Room4::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
  
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    /////////////////////////////
    // 4. all stuff in room

    // background bottom
    auto background1 = Sprite::create(s_r4back1);
    background1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.488);
    this->addChild(background1);

    //background top
    auto background2 = Sprite::create(s_r4back2);
    background2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(background2);

    // left person
    auto pers1 = Sprite::create(s_r4pers1);
    pers1->setPosition(origin.x + visibleSize.width / 4.1, origin.y + visibleSize.height / 1.63);
    this->addChild(pers1);

    // right person
    auto pers2 = Sprite::create(s_r4pers2);
    pers2->setPosition(origin.x + visibleSize.width / 1.803, origin.y + visibleSize.height / 1.63);
    this->addChild(pers2);

    // window parts
    auto winpart = Sprite::create(s_r4winpart);
    winpart->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.488);
    this->addChild(winpart);

    // dialog
    auto dialog = Label::createWithTTF("- What do you think of him?\n- He looks like to be a nice guy\n- but i have a strange feeling about him\n- me too", f_font, 16);
    dialog->setPosition(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 5.8);
    dialog->setTextColor(Color4B::Color4B(195, 163, 138, 255));
    dialog->setLineSpacing(-4);
    this->addChild(dialog);

    /////////////////////////////
    // 5. menu

    // play
    auto play = MenuItemImage::create(s_play, s_play, CC_CALLBACK_1(Room4::PauseScene, this));
    play->setPosition(origin.x + visibleSize.width / 23.8, origin.y + visibleSize.height / 1.078);

    // pause
    auto pause = MenuItemImage::create(s_pause, s_pause, CC_CALLBACK_1(Room4::PauseScene, this));
    pause->setPosition(origin.x + visibleSize.width / 16.4, origin.y + visibleSize.height / 1.078);

    // record
    auto record = MenuItemImage::create(s_record, s_record, CC_CALLBACK_1(Room4::PauseScene, this));
    record->setPosition(origin.x + visibleSize.width / 12.3, origin.y + visibleSize.height / 1.078);

    // stop
    auto stop = MenuItemImage::create(s_stop, s_stop, CC_CALLBACK_1(Room4::PauseScene, this));
    stop->setPosition(origin.x + visibleSize.width / 9.85, origin.y + visibleSize.height / 1.078);

    // menu
    auto menu = Menu::create(play, pause, record, stop, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);

    /////////////////////////////
    // 6. lR parallax

    // left block button
    auto leftblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room4::GoToRoom1, this));
    leftblock->setPosition(origin.x, origin.y + visibleSize.height / 2);

    // right block button
    auto rightblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room4::GoToNewDay, this));
    rightblock->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height / 2);

    // lr buttons
    auto menulr = Menu::create(leftblock, rightblock, NULL);
    menulr->setPosition(Point::ZERO);
    this->addChild(menulr);

    // move to lr
    auto mouseListenerSlide = EventListenerMouse::create();
    mouseListenerSlide->onMouseMove = [=](EventMouse* event) 
    {
        Point mousePosition = Point(event->getCursorX(), event->getCursorY());
        auto moveByBack1 = MoveBy::create(2, Vec2(20, 0));
        auto moveByBack2 = MoveBy::create(2, Vec2(35, 0));
        auto moveByPers1 = MoveBy::create(2, Vec2(35, 0));
        auto moveByPers2 = MoveBy::create(2, Vec2(35, 0));
        auto moveByWin = MoveBy::create(2, Vec2(27, 0));
        if (leftblock->getBoundingBox().containsPoint(mousePosition) && flagL == false) 
        {
            background1->runAction(moveByBack1);
            background2->runAction(moveByBack2);
            pers1->runAction(moveByPers1);
            pers2->runAction(moveByPers2);
            winpart->runAction(moveByWin);
            flagL = true;
        }
        if (leftblock->getBoundingBox().containsPoint(mousePosition) != true && flagL == true) 
        {
            background1->runAction(moveByBack1->reverse());
            background2->runAction(moveByBack2->reverse());
            pers1->runAction(moveByPers1->reverse());
            pers2->runAction(moveByPers2->reverse());
            winpart->runAction(moveByWin->reverse());
            flagL = false;
        }
        if (rightblock->getBoundingBox().containsPoint(mousePosition) && flagR == false) 
        {
            background1->runAction(moveByBack1->reverse());
            background2->runAction(moveByBack2->reverse());
            pers1->runAction(moveByPers1->reverse());
            pers2->runAction(moveByPers2->reverse());
            winpart->runAction(moveByWin->reverse());
            flagR = true;
        }
        if (rightblock->getBoundingBox().containsPoint(mousePosition) != true && flagR == true) 
        {
            background1->runAction(moveByBack1);
            background2->runAction(moveByBack2);
            pers1->runAction(moveByPers1);
            pers2->runAction(moveByPers2);
            winpart->runAction(moveByWin);
            flagR = false;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListenerSlide, this);

    /////////////////////////////
    // 7. clock

    // clock
    this->schedule(CC_SCHEDULE_SELECTOR(Room4::UpdateTimer, f_time));

    return true;
}
void Room4::GoToRoom1(cocos2d::Ref* sender)
{
    auto scene = Room1::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(TRANSITION_TIME, scene));
}
void Room4::GoToNewDay(cocos2d::Ref* sender)
{
    auto scene = NewDay::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITION_TIME, scene));
}
void Room4::PauseScene(cocos2d::Ref* sender)
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
void Room4::UpdateTimer(float dt)
{
    dt = 0.5f;
    f_time += dt;
}