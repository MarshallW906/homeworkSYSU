#include "StartScene.hpp"
#include "StageSelectScene.hpp"
#include "GlobalParams.hpp"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

// on "init" you need to initialize your instance
bool StartScene::init()
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
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Dungeon Mario", "fonts/Marker Felt.ttf", 40);
    label->setTextColor(Color4B(30, 30, 30, 255));
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "StartScene" Background
    // Filename : always backgrounds/StartScene.png
    auto bgmap = Sprite::create("backgrounds/StartScene.jpg");
    bgmap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Size mywinsize=Director::getInstance()->getWinSize();
    float winw = mywinsize.width;
    float winh = mywinsize.height;
    float spx = bgmap->getTextureRect().getMaxX();
    float spy = bgmap->getTextureRect().getMaxY();
    bgmap->setScaleX(winw/spx);
    bgmap->setScaleY(winh/spy);
    this->addChild(bgmap, 0);
    
    // Start Button
    auto startButtonLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 28);
    startButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
    auto startMenuButton = MenuItemLabel::create(startButtonLabel, CC_CALLBACK_1(StartScene::startButtonCallBack, this));
    startMenuButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5 * 3.5));
	
	auto muteButtonLabel = Label::createWithTTF("Mute", "fonts/Marker Felt.ttf", 28);
	if (GlobalParams::Instance().Mute) {
		muteButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
	}
	else {
		muteButtonLabel->setTextColor(Color4B(150, 150, 150, 255));
	}
	auto muteMenuButton = MenuItemLabel::create(muteButtonLabel, CC_CALLBACK_1(StartScene::muteButtonCallBack, this, muteButtonLabel));
	muteMenuButton->setPosition(visibleSize.width - muteButtonLabel->getWidth() - 40, visibleSize.height - muteButtonLabel->getHeight() - 80);

	auto menuStart = Menu::create(startMenuButton, muteMenuButton, NULL);
	menuStart->setPosition(Vec2::ZERO);
    this->addChild(menuStart, 1);

	// add music
	if (!GlobalParams::Instance().Mute) {
		log("Start Scene Play BGM");
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM/TianAnMen.mp3", true);
	}
    
    return true;
}


void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
	SimpleAudioEngine::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
}

void StartScene::startButtonCallBack(Ref* pSender) {
    log("StartScene::startButtonCallBack : clicked start button, change scene to StageSelectScene");
    auto * scene = StageSelectScene::createScene();
    Director::getInstance()->replaceScene(TransitionMoveInR::create(0.5f, scene));
}

void StartScene::muteButtonCallBack(Ref* pSender, cocos2d::Label *muteLabel) {
	GlobalParams::Instance().Mute = !(GlobalParams::Instance().Mute);
	if (GlobalParams::Instance().Mute) {
		muteLabel->setTextColor(Color4B(30, 30, 30, 255));
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		muteLabel->setTextColor(Color4B(150, 150, 150, 255));
		SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM/TianAnMen.mp3", true);
	}
}
