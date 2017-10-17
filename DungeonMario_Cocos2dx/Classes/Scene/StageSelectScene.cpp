//
//  StageSelectScene.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//
#include "SimpleAudioEngine.h"

#include "StartScene.hpp"
#include "StageSelectScene.hpp"
#include "GamePlayingScene.hpp"
#include "GlobalParams.hpp"

#include "cocos2d.h"
USING_NS_CC;

Scene* StageSelectScene::createScene()
{
    return StageSelectScene::create();
}

// on "init" you need to initialize your instance
bool StageSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Stage Select", "fonts/Marker Felt.ttf", 28);
    label->setTextColor(Color4B(30, 30, 30, 255));
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "StageSelect" Background
    // Filename : always backgrounds/StageSelectScene.jpg
    auto bgmap = Sprite::create("backgrounds/StageSelectScene.jpg");
    bgmap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Size mywinsize=Director::getInstance()->getWinSize();
    float winw = mywinsize.width;
    float winh = mywinsize.height;
    float spx = bgmap->getTextureRect().getMaxX();
    float spy = bgmap->getTextureRect().getMaxY();
    bgmap->setScaleX(winw/spx);
    bgmap->setScaleY(winh/spy);
    this->addChild(bgmap, 0);
    
    // Stage Select Buttons
    auto menuSelect = Menu::create();
    for (int i = 1; i <= GlobalParams::Instance().TotalStagesCount; i++) {
        std::stringstream ss;
        ss << i;
        auto stageNumberLabel = Label::createWithTTF(ss.str(), "fonts/Marker Felt.ttf", 40);
        stageNumberLabel->setTextColor(cocos2d::Color4B(30, 30, 30, 255));
        auto stageNumberLabelButton = MenuItemLabel::create(stageNumberLabel, CC_CALLBACK_1(StageSelectScene::selectButtonCallBack, this, i));
        stageNumberLabelButton->setPosition(Vec2(origin.x + visibleSize.width / 4 + visibleSize.width / 2 / 5 * (i - 0.5),
                                                 origin.y + visibleSize.height / 3 * 2));
        menuSelect->addChild(stageNumberLabelButton, 1);
    }
    menuSelect->setPosition(Vec2::ZERO);
    this->addChild(menuSelect, 1);
    
    // HUD : all add to menuHUD
    auto menuHUD = Menu::create();
    auto backButtonLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 28);
    backButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
    auto backButton = MenuItemLabel::create(backButtonLabel, CC_CALLBACK_1(StageSelectScene::backButtonCallback, this));
    backButton->setPosition(visibleSize.width - backButtonLabel->getWidth() - 40, visibleSize.height - backButtonLabel->getHeight() - 40);
    menuHUD->addChild(backButton);
    menuHUD->setPosition(Vec2::ZERO);
    this->addChild(menuHUD, 1);
    
    return true;
}


void StageSelectScene::selectButtonCallBack(cocos2d::Ref* pSender, int stageNumber) {
    log("%d select button clicked", stageNumber);
    log("StageSelectScene::selectButtonCallBack : change scene to GamePlayingScene [with StageNumber: %d]", stageNumber);
    auto * scene = GamePlayingScene::createScene(stageNumber, true);
    Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5f, scene));
}

void StageSelectScene::backButtonCallback(cocos2d::Ref *pSender) {
    log("back Button clicked From StageSelect Scene");
    log("back Button : From StageSelect Scene To StartScene");
    auto * scene = StartScene::createScene();
    Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5f, scene));
}
