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

#include "TableRoom2.h"
#include "Definitions.h"
#include "PauseScene.h"
#include "Room2.h"

USING_NS_CC;

int z2 = 0;

Scene* TableRoom2::createScene()
{
    return TableRoom2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TableRoom2::init()
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

    // background
    auto background = Sprite::create(s_trback);
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(background);

    /////////////////////////////
    // 4. top button

    // top block button
    auto topblock = MenuItemImage::create(s_tbblock, s_tbblock, CC_CALLBACK_1(TableRoom2::GoToRoom2, this));
    topblock->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);

    // t button
    auto menut = Menu::create(topblock, NULL);
    menut->setPosition(Point::ZERO);
    this->addChild(menut);

    /////////////////////////////
    // 5. all stuff on table

    // top layer
    auto layer1 = new (std::nothrow) MainTable2();
    auto layer = LayerMultiplex::create(layer1, nullptr);
    addChild(layer, 0);
    layer1->release();

    /////////////////////////////
    // 6. drag & drop

    // drag & drop
    auto mouseListenerSlide = EventListenerMouse::create();
    mouseListenerSlide->onMouseMove = [=](EventMouse* event)
    {
        Point mousePosition = Point(event->getCursorX(), event->getCursorY());
        auto moveByUpLayer = MoveBy::create(2, Vec2(0, 35));
        if (topblock->getBoundingBox().containsPoint(mousePosition) && flagT == false)
        {
            layer1->runAction(moveByUpLayer->reverse());
            flagT = true;
        }
        if (topblock->getBoundingBox().containsPoint(mousePosition) != true && flagT == true)
        {
            layer1->runAction(moveByUpLayer);
            flagT = false;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListenerSlide, this);

    /////////////////////////////
    // 7. clock

    // clock
    this->schedule(CC_SCHEDULE_SELECTOR(TableRoom2::UpdateTimer, f_time));

    /////////////////////////////
    // 8. menu
    // play
    auto play = MenuItemImage::create(s_play, s_play, CC_CALLBACK_1(TableRoom2::PauseScene, this));
    play->setPosition(origin.x + visibleSize.width / 23.8, origin.y + visibleSize.height / 1.078);

    // pause
    auto pause = MenuItemImage::create(s_pause, s_pause, CC_CALLBACK_1(TableRoom2::PauseScene, this));
    pause->setPosition(origin.x + visibleSize.width / 16.4, origin.y + visibleSize.height / 1.078);

    // record
    auto record = MenuItemImage::create(s_record, s_record, CC_CALLBACK_1(TableRoom2::PauseScene, this));
    record->setPosition(origin.x + visibleSize.width / 12.3, origin.y + visibleSize.height / 1.078);

    // stop
    auto stop = MenuItemImage::create(s_stop, s_stop, CC_CALLBACK_1(TableRoom2::PauseScene, this));
    stop->setPosition(origin.x + visibleSize.width / 9.85, origin.y + visibleSize.height / 1.078);

    // menu
    auto menu = Menu::create(play, pause, record, stop, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);

    return true;
}
void TableRoom2::GoToRoom2(cocos2d::Ref * sender)
{
    auto scene = Room2::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInT::create(TRANSITION_TIME, scene));
}
MainTable2::~MainTable2()
{
}
MainTable2::MainTable2()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 7. all stuff on table

    // ad
    auto ad = Sprite::create(s_trad);
    ad->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(ad);

    // ad clone
    auto adclone = Sprite::create(s_trad);
    adclone->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(adclone);

    // dialog
    auto dialog = Label::createWithTTF("- What do you think of him?\n- He looks like to be a nice guy\n- but i have a strange feeling about him\n- me too", f_font, 16);
    dialog->setPosition(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 1.224);
    dialog->setTextColor(Color4B::Color4B(195, 163, 138, 255));
    dialog->setLineSpacing(-4);
    this->addChild(dialog);

    /////////////////////////////
    // 8. all stuff on table

    // drag & drop

    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [](Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            if (target->getLocalZOrder() > z2)
            {
                z2 = target->getLocalZOrder();
            }
            z2 = z2 + 1;
            target->setLocalZOrder(z2);
            return true;
        }
        return false;
    };
    listener1->onTouchMoved = [](Touch* touch, Event* event)
    {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        auto contentsize = target->getBoundingBox();
        auto pos = target->getPosition();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        if (visibleSize.width >= pos.x + touch->getDelta().x + contentsize.size.width / 2 && pos.x + touch->getDelta().x + contentsize.size.width / 2 >= contentsize.size.width && visibleSize.height / 1.45 >= pos.y + touch->getDelta().y + contentsize.size.height / 2 && pos.y + touch->getDelta().y + contentsize.size.height / 2 >= contentsize.size.height)
        {
            target->setPosition(pos + touch->getDelta());
        }
    };
    listener1->onTouchEnded = [=](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded.. ");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, ad);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), adclone);
}
void TableRoom2::UpdateTimer(float dt)
{
    dt = 0.5f;
    f_time += dt;
}

void TableRoom2::PauseScene(cocos2d::Ref * sender)
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