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

#include "Room2.h"
#include "Definitions.h"
#include "PauseScene.h"
#include "TableRoom2.h"
#include "Room1.h"

USING_NS_CC;

Scene* Room2::createScene()
{
    return Room2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Room2::init()
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
    // 4. all stuff in room

    // background
    auto background = Sprite::create(s_r2back);
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /2);
    this->addChild(background);

    // printer
    auto printer = Sprite::create(s_r2printer);
    printer->setPosition(origin.x + visibleSize.width / 1.275, origin.y + visibleSize.height / 1.681);
    this->addChild(printer);

    // pc
    auto pc = Sprite::create(s_r2pc);
    pc->setPosition(origin.x + visibleSize.width / 1.641, origin.y + visibleSize.height / 1.827);
    this->addChild(pc);

    // monitor
    auto monitor = Sprite::create(s_r2monitor);
    monitor->setPosition(origin.x + visibleSize.width / 2.37, origin.y + visibleSize.height / 1.945);
    this->addChild(monitor);

    // cactus
    auto cactus = Sprite::create(s_r2cactus);
    cactus->setPosition(origin.x + visibleSize.width / 2.443, origin.y + visibleSize.height / 1.25);
    this->addChild(cactus);

    // pen
    auto pen = Sprite::create(s_r2pen);
    pen->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2.4);
    this->addChild(pen);

    // folder
    auto folder = Sprite::create(s_r2folder);
    folder->setPosition(origin.x + visibleSize.width / 6.4, origin.y + visibleSize.height / 2.265);
    this->addChild(folder);

    // lamp
    auto lamp = Sprite::create(s_r2lamp);
    lamp->setPosition(origin.x + visibleSize.width / 5.57, origin.y + visibleSize.height / 1.73);
    this->addChild(lamp);

    // light
    auto light = Sprite::create(s_r2light);
    light->setPosition(origin.x + visibleSize.width / 5.57, origin.y + visibleSize.height / 2.095);
    this->addChild(light);

    // dialog
    auto dialog = Label::createWithTTF("- What do you think of him?\n- He looks like to be a nice guy\n- but i have a strange feeling about him\n- me too", f_font, 16);
    dialog->setPosition(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 5.8);
    dialog->setTextColor(Color4B::Color4B(195, 163, 138, 255));
    dialog->setLineSpacing(-4);
    this->addChild(dialog);

    /////////////////////////////
    // 5. menu

    // play
    auto play = MenuItemImage::create(s_play, s_play, CC_CALLBACK_1(Room2::PauseScene, this));
    play->setPosition(origin.x + visibleSize.width / 23.8, origin.y + visibleSize.height / 1.078);

    // pause
    auto pause = MenuItemImage::create(s_pause, s_pause, CC_CALLBACK_1(Room2::PauseScene, this));
    pause->setPosition(origin.x + visibleSize.width / 16.4, origin.y + visibleSize.height / 1.078);

    // record
    auto record = MenuItemImage::create(s_record, s_record, CC_CALLBACK_1(Room2::PauseScene, this));
    record->setPosition(origin.x + visibleSize.width / 12.3, origin.y + visibleSize.height / 1.078);

    // stop
    auto stop = MenuItemImage::create(s_stop, s_stop, CC_CALLBACK_1(Room2::PauseScene, this));
    stop->setPosition(origin.x + visibleSize.width / 9.85, origin.y + visibleSize.height / 1.078);

    // menu
    auto menu = Menu::create(play, pause, record, stop, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);

    /////////////////////////////
    // 6. rb parallax

    // right block button
    auto rightblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room2::GoToRoom1, this));
    rightblock->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height / 2);

    // bottom block button
    auto bottomblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room2::GoToTable, this));
    bottomblock->setPosition(origin.x + visibleSize.width / 2, origin.y);

    // rb buttons
    auto menulb = Menu::create(rightblock, bottomblock, NULL);
    menulb->setPosition(Point::ZERO);
    this->addChild(menulb);

    // move to rb
    auto mouseListenerSlide = EventListenerMouse::create();
    mouseListenerSlide->onMouseMove = [=](EventMouse* event) 
    {
        Point mousePosition = Point(event->getCursorX(), event->getCursorY());
        auto moveByBack = MoveBy::create(2, Vec2(35, 0));
        auto moveByPrint = MoveBy::create(2, Vec2(32, 0));
        auto moveByPC = MoveBy::create(2, Vec2(30, 0));
        auto moveByMonitor = MoveBy::create(2, Vec2(27, 0));
        auto moveByCactus = MoveBy::create(2, Vec2(27, 0));
        auto moveByPen = MoveBy::create(2, Vec2(22, 0));
        auto moveByFolder = MoveBy::create(2, Vec2(20, 0));
        auto moveByLamp = MoveBy::create(2, Vec2(21, 0));
        auto moveByLight = MoveBy::create(2, Vec2(21, 0));
        auto moveByUpBack = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpPrint = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpPC = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpMonitor = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpCactus = MoveBy::create(2, Vec2(0, 30));
        auto moveByUpPen = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpFolder = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpLamp = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpLight = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpDial = MoveBy::create(2, Vec2(0, 35));
        if (rightblock->getBoundingBox().containsPoint(mousePosition) && flagR == false) 
        {
            background->runAction(moveByBack->reverse());
            printer->runAction(moveByPrint->reverse());
            pc->runAction(moveByPC->reverse());
            monitor->runAction(moveByMonitor->reverse());
            cactus->runAction(moveByCactus->reverse());
            pen->runAction(moveByPen->reverse());
            folder->runAction(moveByFolder->reverse());
            lamp->runAction(moveByLamp->reverse());
            light->runAction(moveByLight->reverse());
            flagR = true;
        }
        if (rightblock->getBoundingBox().containsPoint(mousePosition) != true && flagR == true) 
        {
            background->runAction(moveByBack);
            printer->runAction(moveByPrint);
            pc->runAction(moveByPC);
            monitor->runAction(moveByMonitor);
            cactus->runAction(moveByCactus);
            pen->runAction(moveByPen);
            folder->runAction(moveByFolder);
            lamp->runAction(moveByLamp);
            light->runAction(moveByLight);
            flagR = false;
        }
        if (bottomblock->getBoundingBox().containsPoint(mousePosition) && flagB == false) 
        {
            background->runAction(moveByUpBack);
            printer->runAction(moveByUpPrint);
            pc->runAction(moveByUpPC);
            monitor->runAction(moveByUpMonitor);
            cactus->runAction(moveByUpCactus);
            pen->runAction(moveByUpPen);
            folder->runAction(moveByUpFolder);
            lamp->runAction(moveByUpLamp);
            light->runAction(moveByUpLight);
            dialog->runAction(moveByUpDial);
            flagB = true;
        }
        if (bottomblock->getBoundingBox().containsPoint(mousePosition) != true && flagB == true) 
        {
            background->runAction(moveByUpBack->reverse());
            printer->runAction(moveByUpPrint->reverse());
            pc->runAction(moveByUpPC->reverse());
            monitor->runAction(moveByUpMonitor->reverse());
            cactus->runAction(moveByUpCactus->reverse());
            pen->runAction(moveByUpPen->reverse());
            folder->runAction(moveByUpFolder->reverse());
            lamp->runAction(moveByUpLamp->reverse());
            light->runAction(moveByUpLight->reverse());
            dialog->runAction(moveByUpDial->reverse());
            flagB = false;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListenerSlide, this);

    /////////////////////////////
    // 7. clock

    // clock
    this->schedule(CC_SCHEDULE_SELECTOR(Room2::UpdateTimer, f_time));

    return true;
}
void Room2::GoToRoom1(cocos2d::Ref* sender)
{
    auto scene = Room1::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITION_TIME, scene));
}
void Room2::GoToTable(cocos2d::Ref* sender)
{
    auto scene = TableRoom2::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(TRANSITION_TIME, scene));
}
void Room2::PauseScene(cocos2d::Ref* sender)
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
void Room2::UpdateTimer(float dt)
{
    dt = 0.5f;
    f_time += dt;
}