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

#include "PauseScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
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
    auto background = Sprite::create(s_pauseback);
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    background->setLocalZOrder(10);
    this->addChild(background);

    /////////////////////////////
    // 4. menu

    // font settings
    MenuItemFont::setFontName(f_font);
    MenuItemFont::setFontSize(16);

    // continue
    auto continueItem = MenuItemFont::create("Continue", CC_CALLBACK_1(PauseScene::GoBack, this));
    continueItem->setColor(Color3B::Color3B(195, 163, 138));
    continueItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.63 + origin.y));

    // settings
    auto settingsItem = MenuItemFont::create("Settings", CC_CALLBACK_1(PauseScene::menuCallback, this));
    settingsItem->setEnabled(false);
    settingsItem->setColor(Color3B::Color3B(195, 163, 138));
    settingsItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.865 + origin.y));

    // mainmenu
    auto backmenuItem = MenuItemFont::create("mainmenu", CC_CALLBACK_1(PauseScene::GoToMainMenu, this));
    backmenuItem->setColor(Color3B::Color3B(195, 163, 138));
    backmenuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.17 + origin.y));

    // exit game
    auto closeItem = MenuItemFont::create("Exit", CC_CALLBACK_1(PauseScene::menuCloseCallback, this));
    closeItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.61 + origin.y));
    closeItem->setColor(Color3B::Color3B(195, 163, 138));

    // menu
    auto menu = Menu::create(continueItem, settingsItem, backmenuItem, closeItem, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(11);
    this->addChild(menu);
}
void PauseScene::menuCallback(Ref* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<MenuItemToggle*>(sender)->selectedItem(), dynamic_cast<MenuItemToggle*>(sender)->selectedIndex() ); 
}
void PauseScene::GoBack(cocos2d::Ref* sender)
{
    Director::getInstance()->popScene();
}
void PauseScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
}
void PauseScene::GoToMainMenu(cocos2d::Ref* sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}