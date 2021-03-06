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

#include "Room3.h"
#include "Definitions.h"
#include "PauseScene.h"
#include "Room1.h"

USING_NS_CC;

Scene* Room3::createScene()
{
    return Room3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Room3::init()
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

    // background
    auto background = Sprite::create(s_r3back);
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(background);

    // left suspect 
    auto susp1 = Sprite::create(s_r3susp1);
    susp1->setPosition(origin.x + visibleSize.width / 4.24, origin.y + visibleSize.height / 1.587);
    this->addChild(susp1);

    // right suspect
    auto susp2 = Sprite::create(s_r3susp2);
    susp2->setPosition(origin.x + visibleSize.width / 1.422, origin.y + visibleSize.height / 1.747);
    this->addChild(susp2);

    // dialog
    auto dialog = Label::createWithTTF("- What do you think of him?\n- He looks like to be a nice guy\n- but i have a strange feeling about him\n- me too", f_font, 16);
    dialog->setPosition(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 5.8);
    dialog->setTextColor(Color4B::Color4B(195, 163, 138, 255));
    dialog->setLineSpacing(-4);
    this->addChild(dialog);

    /////////////////////////////
    // 5. menu

    // play
    auto play = MenuItemImage::create(s_play, s_play, CC_CALLBACK_1(Room3::PauseScene, this));
    play->setPosition(origin.x + visibleSize.width / 23.8, origin.y + visibleSize.height / 1.078);

    // pause
    auto pause = MenuItemImage::create(s_pause, s_pause, CC_CALLBACK_1(Room3::PauseScene, this));
    pause->setPosition(origin.x + visibleSize.width / 16.4, origin.y + visibleSize.height / 1.078);

    // record
    auto record = MenuItemImage::create(s_record, s_record, CC_CALLBACK_1(Room3::PauseScene, this));
    record->setPosition(origin.x + visibleSize.width / 12.3, origin.y + visibleSize.height / 1.078);

    // stop
    auto stop = MenuItemImage::create(s_stop, s_stop, CC_CALLBACK_1(Room3::PauseScene, this));
    stop->setPosition(origin.x + visibleSize.width / 9.85, origin.y + visibleSize.height / 1.078);

    // menu
    auto menu = Menu::create(play, pause, record, stop, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);

    /////////////////////////////
    // 6. lb parallax

    // bottom block button
    auto bottomblock = MenuItemImage::create(s_lrblock, s_lrblock, CC_CALLBACK_1(Room3::GoToRoom1, this));
    bottomblock->setPosition(origin.x + visibleSize.width / 2, origin.y);

    // lb buttons
    auto menulb = Menu::create(bottomblock, NULL);
    menulb->setPosition(Point::ZERO);
    this->addChild(menulb);

    // move to lb
    auto mouseListenerSlide = EventListenerMouse::create();
    mouseListenerSlide->onMouseMove = [=](EventMouse* event) 
    {
        Point mousePosition = Point(event->getCursorX(), event->getCursorY());
        auto moveByBack = MoveBy::create(2, Vec2(35, 0));
        auto moveBySusp1 = MoveBy::create(2, Vec2(28, 0));
        auto moveBySusp2 = MoveBy::create(2, Vec2(23, 0));
        auto moveByUpBack = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpSusp1 = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpSusp2 = MoveBy::create(2, Vec2(0, 35));
        auto moveByUpDial = MoveBy::create(2, Vec2(0, 35));
        if (bottomblock->getBoundingBox().containsPoint(mousePosition) && flagR == false) 
        {
            background->runAction(moveByUpBack);
            susp1->runAction(moveByUpSusp1);
            susp2->runAction(moveByUpSusp2);
            flagR = true;
        }
        if (bottomblock->getBoundingBox().containsPoint(mousePosition) != true && flagR == true)
        {
            background->runAction(moveByUpBack->reverse());
            susp1->runAction(moveByUpSusp1->reverse());
            susp2->runAction(moveByUpSusp2->reverse());
            flagR = false;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListenerSlide, this);

    /////////////////////////////
    // 7. clock

    // clock
    this->schedule(CC_SCHEDULE_SELECTOR(Room3::UpdateTimer, f_time));

    return true;
}
void Room3::GoToRoom1(cocos2d::Ref* sender)
{
    auto scene = Room1::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInB::create(TRANSITION_TIME, scene));
}
void Room3::PauseScene(cocos2d::Ref* sender)
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
void Room3::UpdateTimer(float dt)
{
    dt = 0.5f;
    f_time += dt;
}