//
//  CreditScene.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//

#include "CreditScene.hpp"
#include "StartScene.hpp"
#include "GlobalParams.hpp"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* CreditScene::createScene()
{
    return CreditScene::create();
}

// on "init" you need to initialize your instance
bool CreditScene::init()
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
    auto label = Label::createWithTTF("Congratulations", "fonts/Marker Felt.ttf", 40);
    label->setTextColor(Color4B(30, 30, 30, 255));
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    auto bgmap = Sprite::create("backgrounds/CreditScene.jpg");
    bgmap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Size mywinsize=Director::getInstance()->getWinSize();
    float winw = mywinsize.width;
    float winh = mywinsize.height;
    float spx = bgmap->getTextureRect().getMaxX();
    float spy = bgmap->getTextureRect().getMaxY();
    bgmap->setScaleX(winw/spx);
    bgmap->setScaleY(winh/spy);
    this->addChild(bgmap, 0);
    
    // HUD : all add to menuHUD
	auto menuHUD = Menu::create();
	auto backButtonLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 28);
	backButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
	auto backButton = MenuItemLabel::create(backButtonLabel, CC_CALLBACK_1(CreditScene::backButtonCallback, this));
	backButton->setPosition(visibleSize.width - backButtonLabel->getWidth() - 40, visibleSize.height - backButtonLabel->getHeight() - 40);
	menuHUD->addChild(backButton);

	menuHUD->setPosition(Vec2::ZERO);
	this->addChild(menuHUD, 1);

	if (!GlobalParams::Instance().Mute) {
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playEffect("mp3/BGM/Congratulations.mp3");
	}
    
    return true;
}


void CreditScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    

}

void CreditScene::backButtonCallback(cocos2d::Ref *pSender) {
    log("back Button clicked From Credit Scene");
    log("back Button : From Credit Scene To StartScene");
    auto * scene = StartScene::createScene();
    Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5f, scene));
}
