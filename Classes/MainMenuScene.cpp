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

#include "MainMenuScene.h"
#include "Definitions.h"
#include "Room1.h"
#include "TutorialScene.h"

USING_NS_CC;

Size visibleSize;
Vec2 origin;

enum 
{
    kTagNode
};

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // still in work, indentify current language//
    //LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();

    /////////////////////////////
    // 4. menu

    // game menu
    auto layer1 = new (std::nothrow) MainMenu();
    layer1->setLocalZOrder(1);
    auto layer2 = new (std::nothrow) MenuLayer();
    layer2->setLocalZOrder(2);
    auto layer = LayerMultiplex::create(layer1, layer2, nullptr);
    addChild(layer, 0);
    layer1->release();
    layer2->release();

    // game logo
    auto MenuLogoSceneSprite = Sprite::create(s_menulogo);
    MenuLogoSceneSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.45 + origin.y));
    MenuLogoSceneSprite->setLocalZOrder(1);
    this->addChild(MenuLogoSceneSprite);
    
    /////////////////////////////
    // 5. parallax + background
    // top sprite shadow
    auto topSprite = Sprite::create(s_menuback1);
    topSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    topSprite->setLocalZOrder(0);
    this->addChild(topSprite);

    // back sprite background
    auto backSprite = Sprite::create(s_menuback2);
    backSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backSprite->setLocalZOrder(-8);
    this->addChild(backSprite);

    // mouse listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(MainMenuScene::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 1st image parallax
    auto parallaxImage1 = Sprite::create(s_menuback3);
    parallaxImage1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallaxImage1->setAnchorPoint(Vec2(0, 0));

    // 2nd image parallax
    auto parallaxImage2 = Sprite::create(s_menuback4);
    parallaxImage2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallaxImage2->setAnchorPoint(Vec2(0, 0));

    // 3rd image parallax
    auto parallaxImage3 = Sprite::create(s_menuback5);
    parallaxImage3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallaxImage3->setAnchorPoint(Vec2(0, 0));
 
    // 4th image parallax
    auto parallaxImage4 = Sprite::create(s_menuback6);
    parallaxImage4->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallaxImage4->setAnchorPoint(Vec2(0, 0));
    
    //5th image parallax
    auto parallaxImage5 = Sprite::create(s_menuback7);
    parallaxImage5->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallaxImage5->setAnchorPoint(Vec2(0, 0));

    // create a void node, a parent node
    auto voidNode = ParallaxNode::create();

    // 5th image is moved at a ratio of 0.0005x, 0.y
    voidNode->addChild(parallaxImage5, -3, Vec2(0.0005f, 0.0f), Vec2::ZERO);

    // 4th image is moved at a ratio of 0.001x, 0.y
    voidNode->addChild(parallaxImage4, -2, Vec2(0.001f, 0.0f), Vec2::ZERO);

    // 3rd image is moved at a ratio of 0.002x, 0.y
    voidNode->addChild(parallaxImage3, -1, Vec2(0.002f, 0.f), Vec2::ZERO);

    // 2nd image is moved at a ratio of 0.003x, 0.y
    voidNode->addChild(parallaxImage2, 1, Vec2(0.003f, 0.0f), Vec2::ZERO);

    // 1st image is moved at a ratio of 0.004x, 0.y
    voidNode->addChild(parallaxImage1, 2, Vec2(0.004f, 0.0f), Vec2::ZERO);

    // final parallax
    addChild(voidNode, 1, kTagNode);
    voidNode->setLocalZOrder(-7);
    
    return true;
}

void MainMenuScene::onMouseMove(Event* event)
{
    EventMouse* coursor = (EventMouse*)event;
    visibleSize = Director::getInstance()->getVisibleSize();
    auto curpos = coursor->getCursorX();
    auto parallax = getChildByTag(kTagNode);
    auto parpos = parallax->getPosition();
    auto parsize = parallax->getBoundingBox().size;
    if (curpos > visibleSize.width / 2 && parpos.x < visibleSize.width - parsize.width) 
    {
        auto moveBy = MoveBy::create(2, Vec2(curpos*1.5, 0));
        auto easeAction = EaseQuadraticActionInOut::create(moveBy);
        parallax->runAction(easeAction);
    }
    else if (curpos < visibleSize.width / 2 && parpos.x > 0 - parsize.width)
    {
        auto moveBy = MoveBy::create(2, Vec2(-curpos*1.5, 0));
        auto easeAction = EaseQuadraticActionInOut::create(moveBy);
        parallax->runAction(easeAction);
    }
}
MainMenu::~MainMenu()
{
}
MainMenu::MainMenu()
{
    // font settings
    MenuItemFont::setFontName(f_font);
    MenuItemFont::setFontSize(15);

    // continue
    auto continueItem = MenuItemFont::create("Continue", CC_CALLBACK_1(MainMenu::GoToRoom1, this));
    continueItem->setColor(Color3B::Color3B(195, 163, 138));
    continueItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.81 + origin.y));

    // new  game
    auto playItem = MenuItemFont::create("New Game", CC_CALLBACK_1(MainMenu::GoToTutorialScene, this));
    playItem->setColor(Color3B::Color3B(195, 163, 138));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.105 + origin.y));

    // settings
    auto settingsItem = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::menuCallback, this));
    settingsItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.518 + origin.y));
    settingsItem->setColor(Color3B::Color3B(195, 163, 138));

    // exit game
    auto closeItem = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    closeItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3.13 + origin.y));
    closeItem->setColor(Color3B::Color3B(195, 163, 138));

    // menu
    auto menu = Menu::create(continueItem, playItem, settingsItem, closeItem, NULL);
    menu->setPosition(Point::ZERO);
    menu->setLocalZOrder(1);
    this->addChild(menu);
}
void MainMenu::menuCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(1, false);
}
void MainMenu::GoToRoom1(cocos2d::Ref* sender)
{
    auto scene = Room1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void MainMenu::GoToTutorialScene(cocos2d::Ref* sender)
{
    auto scene = TutorialScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void MainMenu::menuCloseCallback(cocos2d::Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
}
MenuLayer::~MenuLayer()
{
}
MenuLayer::MenuLayer()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // font settings
    MenuItemFont::setFontName(f_font);
    MenuItemFont::setFontSize(15);

    // sound
    auto soundon = MenuItemFont::create("On");
    soundon->setColor(Color3B::Color3B(195, 163, 138));
    auto soundoff = MenuItemFont::create("Off");
    soundoff->setColor(Color3B::Color3B(195, 163, 138));
    auto musicon = MenuItemFont::create("On");
    musicon->setColor(Color3B::Color3B(195, 163, 138));
    auto musicoff = MenuItemFont::create("Off");
    musicoff->setColor(Color3B::Color3B(195, 163, 138));
    auto rus = MenuItemFont::create("Rus");
    rus->setColor(Color3B::Color3B(195, 163, 138));
    auto eng = MenuItemFont::create("Eng");
    eng->setColor(Color3B::Color3B(195, 163, 138));

    // sound
    auto soundItem = MenuItemFont::create("Sound", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    soundItem->setEnabled(false);   
    soundItem->setColor(Color3B::Color3B(195, 163, 138));
    soundItem->setPosition(Point(visibleSize.width / 2.1 + origin.x, visibleSize.height / 1.8 + origin.y));

    // sound toggle
    auto soundItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::menuCallback, this),
        soundon,
        soundoff,
        nullptr);
    soundItemToggle->setPosition(Point(visibleSize.width / 1.83 + origin.x, visibleSize.height / 1.8 + origin.y));

    // music
    auto musicItem = MenuItemFont::create("Music", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    musicItem->setEnabled(false);
    musicItem->setColor(Color3B::Color3B(195, 163, 138));
    musicItem->setPosition(Point(visibleSize.width / 2.1 + origin.x, visibleSize.height / 2.1 + origin.y));

    // music toggle
    auto musicItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::menuCallback, this),
        musicon,
        musicoff,
        nullptr);
    musicItemToggle->setPosition(Point(visibleSize.width / 1.83 + origin.x, visibleSize.height / 2.1 + origin.y));

    // language
    auto languageItem = MenuItemFont::create("Language", CC_CALLBACK_1(MenuLayer::menuCallback, this));
    languageItem->setEnabled(false);
    languageItem->setColor(Color3B::Color3B(195, 163, 138));
    languageItem->setPosition(Point(visibleSize.width / 2.15 + origin.x, visibleSize.height / 2.5 + origin.y));

    // language toggle
    auto languageItemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::menuCallback, this),
        rus,
        eng,
        nullptr);
    languageItemToggle->setPosition(Point(visibleSize.width / 1.78 + origin.x, visibleSize.height / 2.5 + origin.y));

    // go back
    auto gobackItem = MenuItemFont::create("Go back", CC_CALLBACK_1(MenuLayer::backCallback, this));
    gobackItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3.1 + origin.y));
    gobackItem->setColor(Color3B::Color3B(195, 163, 138));

    // create menu + position
    auto menu = Menu::create(
        soundItem, soundItemToggle,
        musicItem, musicItemToggle,
        languageItem, languageItemToggle,
        gobackItem, nullptr); // 7 items.
    addChild(menu);
    menu->setPosition(Point::ZERO);
}
void MenuLayer::menuCallback(Ref* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<MenuItemToggle*>(sender)->selectedItem(), dynamic_cast<MenuItemToggle*>(sender)->selectedIndex() ); 
}
void MenuLayer::backCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0, false);
}