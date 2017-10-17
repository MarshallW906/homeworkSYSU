//
//  GamePlayingScene.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//

#include "GamePlayingScene.hpp"

#pragma execution_character_set("utf-8")
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalParams.hpp"
#include "Player/MarioPlayer.hpp"

#include "StageSelectScene.hpp"
#include "CreditScene.hpp"

#define database UserDefault::getInstance()

USING_NS_CC;

using namespace CocosDenshion;

void GamePlayingScene::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* GamePlayingScene::createScene(int currentStageNumber = 1, bool changeBGM = true)
{
    srand((unsigned)time(NULL));
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setAutoStep(true);
    
    // Debug mode
    // 开启debug模式需要setAutoStep(true) 并注释掉update函数第一行
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0, -600.0f));
    auto layer = GamePlayingScene::create(currentStageNumber, changeBGM);
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayingScene::init(int currentStageNumber = 1, bool changeBGM = true)
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    GlobalParams::Instance().keys.clear();
    this->StageNumber = currentStageNumber;
    log("Enter a new GamePlayingScene. StageNumber:[%d]", this->StageNumber);
    
    loadMusic(changeBGM);
    addHUD();
    loadMap();
    addPlayer();
    addListener();
    
    switch (this->StageNumber) {
        case 1:
            loadStage1();
            break;
        case 2:
            loadStage2();
            break;
        case 3:
            loadStage3();
        default:
            break;
    }
    
    // add scheduler
    schedule(schedule_selector(GamePlayingScene::update), 0.01f, kRepeatForever, 0.1f);
    schedule(schedule_selector(::GamePlayingScene::updatePerSec), 1.0f, kRepeatForever, 0);
    
    
    return true;
}

void GamePlayingScene::addHUD() {
    // HUD : all add to menuHUD
    auto menuHUD = Menu::create();
    auto backButtonLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 28);
    backButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
    auto backButton = MenuItemLabel::create(backButtonLabel, CC_CALLBACK_1(GamePlayingScene::backButtonCallback, this));
	backButton->setPosition(visibleSize.width - backButtonLabel->getWidth() - 40, visibleSize.height - backButtonLabel->getHeight() - 40);
    menuHUD->addChild(backButton);

	auto muteButtonLabel = Label::createWithTTF("Mute", "fonts/Marker Felt.ttf", 28);
	if (GlobalParams::Instance().Mute) {
		muteButtonLabel->setTextColor(Color4B(30, 30, 30, 255));
	}
	else {
		muteButtonLabel->setTextColor(Color4B(150, 150, 150, 255));
	}
	auto muteMenuButton = MenuItemLabel::create(muteButtonLabel, CC_CALLBACK_1(GamePlayingScene::muteButtonCallBack, this, muteButtonLabel));
	muteMenuButton->setPosition(visibleSize.width - muteButtonLabel->getWidth() - 40, visibleSize.height - muteButtonLabel->getHeight() - 80);
	menuHUD->addChild(muteMenuButton);

    menuHUD->setPosition(Vec2::ZERO);
    this->addChild(menuHUD, 1);
}

void GamePlayingScene::addListener() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GamePlayingScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GamePlayingScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayingScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GamePlayingScene::update(float dt) {
    Node::update(dt);
    if (currentPlayer != nullptr)
        currentPlayer->update();
    if (currentStartPoint != nullptr)
        currentStartPoint->update();
    if (currentDestinationPoint != nullptr)
        currentDestinationPoint->update();
    if (currentKey != nullptr)
        currentKey->update();
    
    for (auto &t : currentPlainRocks) t.update();
    for (auto &t : currentIceRocks) t.update();
    
    for (auto &t : currentMushrooms) t.update();
    for (auto &t : currentCoins) t.update();
    for (auto &t : currentFlyingPlatforms) t.update();
    for (auto &t : currentTanhuangs) t.update();
    
    for (auto &t : currentTurtles) t.update();
    for (auto &t : currentChestnuts) t.update();
    for (auto &t : currentGears) t.update();
    
}

void GamePlayingScene::updatePerSec(float dt) {
    currentTimeCount++;
    if (currentPlayer != nullptr)
        currentPlayer->updatePerSec();
    if (currentStartPoint != nullptr)
        currentStartPoint->updatePerSec();
    if (currentDestinationPoint != nullptr)
        currentDestinationPoint->updatePerSec();
    if (currentKey != nullptr)
        currentKey->updatePerSec();
    
    for (auto &t : currentPlainRocks) t.updatePerSec();
    for (auto &t : currentIceRocks) t.updatePerSec();
    
    for (auto &t : currentMushrooms) t.updatePerSec();
    for (auto &t : currentCoins) t.updatePerSec();
    for (auto &t : currentFlyingPlatforms) t.updatePerSec();
    for (auto &t : currentTanhuangs) t.updatePerSec();
    
    for (auto &t : currentTurtles) t.updatePerSec();
    for (auto &t : currentChestnuts) t.updatePerSec();
    for (auto &t : currentGears) t.updatePerSec();
    
    if (currentPlayer->getPlayerSprite()->getPosition().y < origin.y - 50) {
        auto scene = GamePlayingScene::createScene(this->StageNumber, false);
        Director::getInstance()->replaceScene(scene);
    }
}

void GamePlayingScene::releaseObjects() {
    delete currentPlayer;
    delete currentStartPoint;
    delete currentDestinationPoint;
    delete currentKey;
}

void GamePlayingScene::addPlayer() {
    currentPlayer = new MarioPlayer();
    currentPlayer->getPlayerSprite()->setPosition(visibleSize.width / 4, visibleSize.height / 4);
    this->addChild(currentPlayer->getPlayerSprite(), 1);
}

void GamePlayingScene::loadAnimation(std::string filepath) {
    // done in Appdelegate.cpp
}

void GamePlayingScene::loadMusic(bool changeBGM = true) {
    // need music
	if (changeBGM) {
		if (!GlobalParams::Instance().Mute) {
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM/SMBSM3DL_4.mp3", true);
		}
	} else {
		if (!GlobalParams::Instance().Mute) {
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
}

void GamePlayingScene::loadStage1() {
    // load map
    log("load tmux map");
    /*
    std::stringstream strss;
    strss << "TmuxMap/stage" << StageNumber << ".tmx";
    currentStageTmx = TMXTiledMap::create(strss.str());
     */
    currentStageTmx = TMXTiledMap::create("TmuxMap/testmap.tmx");
    currentStageTmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    currentStageTmx->setAnchorPoint(Vec2(0.5f, 0.5f));
    currentStageTmx->setScale(Director::getInstance()->getContentScaleFactor());
    auto scale = Director::getInstance()->getContentScaleFactor();
    log("%f", scale);
    this->addChild(currentStageTmx, 0);
    
    
    // add ship
    auto ship = Sprite::create("ObjectPics/testShip.png");
    ship->setScale(visibleSize.width / ship->getContentSize().width * 0.97, 1.2f);
    ship->setPosition(visibleSize.width / 2, 110);
    auto shipbody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 1.0f));
    shipbody->setCategoryBitmask(0xFFFFFFFF);
    shipbody->setCollisionBitmask(0xFFFFFFFF);
    shipbody->setContactTestBitmask(0xFFFFFFFF);
    shipbody->setGravityEnable(false);
    shipbody->setDynamic(false);
    ship->setPhysicsBody(shipbody);
    this->addChild(ship, 1);
    
    PlainRock testPlainRock;
    testPlainRock.setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 4));
    currentPlainRocks.push_back(testPlainRock);
    this->addChild(testPlainRock.getRelatedCCSprite(), 1);
    
    IceRock testIceRock;
    testIceRock.setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 4));
    currentIceRocks.push_back(testIceRock);
    this->addChild(testIceRock.getRelatedCCSprite(), 1);
    
    Tanhuang testTanhuang;
    testTanhuang.setPosition(Vec2(visibleSize.width / 3 * 1.5, visibleSize.height / 4));
    currentTanhuangs.push_back(testTanhuang);
    this->addChild(testTanhuang.getRelatedCCSprite(), 1);
    
    Mushroom testMushroom;
    testMushroom.setPosition(Vec2(visibleSize.width / 3 * 2.5, visibleSize.height / 4));
    currentMushrooms.push_back(testMushroom);
    this->addChild(testMushroom.getRelatedCCSprite(), 1);
    
    currentKey = new KeyToNextstage;
    currentKey->setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 4));
    this->addChild(currentKey->getRelatedCCSprite(), 1);
    
    FlyingPlatform testPlatform;
    currentFlyingPlatforms.push_back(testPlatform);
    testPlatform.setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 5 * 2));
    this->addChild(testPlatform.getRelatedCCSprite(), 1);
    testPlatform.startPlaying();
    
    currentDestinationPoint = new DestinationPoint();
    currentDestinationPoint->setPosition(Vec2(visibleSize.width / 3 * 2.5, visibleSize.height / 2));
    this->addChild(currentDestinationPoint->getRelatedCCSprite(), 1);
    
    FlyingTurtle testTurtle;
    currentTurtles.push_back(testTurtle);
    testTurtle.setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
    testTurtle.startPlaying();
    this->addChild(testTurtle.getRelatedCCSprite());
    
    Gear testGear;
    currentGears.push_back(testGear);
    testGear.setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 3));
    this->addChild(testGear.getRelatedCCSprite());
    
}

void GamePlayingScene::loadStage2() {
    for (int i = 0; i < 20; i++) {
        IceRock groundIceRock;
        groundIceRock.setPosition(Vec2(origin.x + (i - 1) * 32, origin.y + visibleSize.height / 5 - 32));
        currentIceRocks.push_back(groundIceRock);
        this->addChild(groundIceRock.getRelatedCCSprite(), 1);
    }
    
    Tanhuang tanhuang1, tanhuang2;
    tanhuang1.setPosition(Vec2(7 * 32, visibleSize.height / 4 + 32));
    tanhuang2.setPosition(Vec2(25 * 32, visibleSize.height / 5 * 2));
    currentTanhuangs.push_back(tanhuang1);
    currentTanhuangs.push_back(tanhuang2);
    this->addChild(tanhuang1.getRelatedCCSprite(), 1);
    this->addChild(tanhuang2.getRelatedCCSprite(), 1);
    
    PlainRock plainRocks[5];
    plainRocks[0].setPosition(Vec2(tanhuang1.getRelatedCCSprite()->getPosition().x, visibleSize.height / 5 * 3));
    plainRocks[1].setPosition(Vec2(10 * 32, visibleSize.height / 5 * 3));
    plainRocks[2].setPosition(Vec2(12 * 32, visibleSize.height / 5 * 3));
    plainRocks[3].setPosition(Vec2(17 * 32, visibleSize.height / 5 * 3));
    plainRocks[4].setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 5 * 4));
    for (int i = 0; i < 5; i++) {
        this->addChild(plainRocks[i].getRelatedCCSprite(), 1);
    }
    
    currentDestinationPoint = new DestinationPoint;
    currentDestinationPoint->setPosition(plainRocks[4].getRelatedCCSprite()->getPosition() + Vec2(0, 32));
    this->addChild(currentDestinationPoint->getRelatedCCSprite(), 1);
    
    Gear gears[6];
    gears[0].setPosition(Vec2(20 * 32, visibleSize.height / 5 + 16));
    gears[1].setPosition(plainRocks[2].getRelatedCCSprite()->getPosition() + Vec2(32, 32));
    gears[2].setPosition(plainRocks[2].getRelatedCCSprite()->getPosition() + Vec2(64, 32));
    gears[3].setPosition(plainRocks[2].getRelatedCCSprite()->getPosition() + Vec2(128, 32));
    gears[4].setPosition(tanhuang2.getRelatedCCSprite()->getPosition() + Vec2(-32 * 3, 32 * 4));
    gears[5].setPosition(Vec2(26 * 32, visibleSize.height / 4 + 32));
    for (int i = 0; i < 6; i++) {
        this->addChild(gears[i].getRelatedCCSprite(), 1);
    }
    
    currentKey = new KeyToNextstage;
    currentKey->setPosition(Vec2(visibleSize.width / 5 * 4, visibleSize.height / 5));
    this->addChild(currentKey->getRelatedCCSprite(), 1);
    
    FlyingPlatform platfrom1;
    currentFlyingPlatforms.push_back(platfrom1);
    platfrom1.setPosition(Vec2(visibleSize.width / 5 * 4 - 3 * 32, visibleSize.height / 5 - 32));
    platfrom1.startPlaying();
    this->addChild(platfrom1.getRelatedCCSprite(), 1);
    
}

void GamePlayingScene::loadStage3() {
    for (int i = 0; i < 15; i++) {
        IceRock groundIceRock;
        groundIceRock.setPosition(Vec2(origin.x + (i - 1) * 32, origin.y + visibleSize.height / 5 - 32));
        currentIceRocks.push_back(groundIceRock);
        this->addChild(groundIceRock.getRelatedCCSprite(), 1);
    }
    
    for (int i = 0; i < 5; i++) {
        FlyingTurtle tmpTurtle;
        tmpTurtle.setPosition(Vec2(origin.x + (15 + i * 3) * 32, visibleSize.height / 5 + i * 2 * 32));
        currentTurtles.push_back(tmpTurtle);
		tmpTurtle.startPlaying();
        this->addChild(tmpTurtle.getRelatedCCSprite(), 1);
    }
    
    currentKey = new KeyToNextstage;
    currentKey->setPosition(Vec2(origin.x + 21 * 32, visibleSize.height / 5 * 3.5));
    this->addChild(currentKey->getRelatedCCSprite(), 1);
    
    currentDestinationPoint = new DestinationPoint;
    currentDestinationPoint->setPosition(Vec2(origin.x + 28 * 32, visibleSize.height / 5 * 4));
    this->addChild(currentDestinationPoint->getRelatedCCSprite(), 1);
}

void GamePlayingScene::loadMap() {
    auto bgmap = Sprite::create("backgrounds/GamePlayingScene.jpg");
    bgmap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Size mywinsize=Director::getInstance()->getWinSize();
    float winw = mywinsize.width;
    float winh = mywinsize.height;
    float spx = bgmap->getTextureRect().getMaxX();
    float spy = bgmap->getTextureRect().getMaxY();
    bgmap->setScaleX(winw/spx);
    bgmap->setScaleY(winh/spy);
    this->addChild(bgmap, 0);
}

void GamePlayingScene::onKeyPressed(EventKeyboard::KeyCode code, Event * event) {
    GlobalParams::Instance().keys[code] = true;
    switch (code) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            currentPlayer->jump();
            break;
            
        default:
            break;
    }
}

void GamePlayingScene::onKeyReleased(EventKeyboard::KeyCode code, Event * event) {
    GlobalParams::Instance().keys[code] = false;
}

bool GamePlayingScene::onContactBegin(cocos2d::PhysicsContact & contact) {
    auto physicsBodyA = contact.getShapeA()->getBody(),
        physicsBodyB = contact.getShapeB()->getBody();
    auto tagA = physicsBodyA->getTag(), tagB = physicsBodyB->getTag();
    if (tagA == GlobalParams::Instance().TagMap["PlayerPhysics"] || tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        currentPlayer->onCollisionWithMap();
    }
    
    if (tagA == GlobalParams::Instance().TagMap["TanhuangPhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        Tanhuang::onContactWithPlayer(physicsBodyA, currentPlayer->getPlayerSprite());
    } else if (tagB == GlobalParams::Instance().TagMap["TanhuangPhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        Tanhuang::onContactWithPlayer(physicsBodyB, currentPlayer->getPlayerSprite());
    }
    
    if (tagA == GlobalParams::Instance().TagMap["MushroomPhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player ImmunityOnce");
        Mushroom::onContactWithPlayer(physicsBodyA);
        currentPlayer->setImmunityOnce();
    } else if (tagB == GlobalParams::Instance().TagMap["MushroomPhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player ImmunityOnce");
        Mushroom::onContactWithPlayer(physicsBodyB);
        currentPlayer->setImmunityOnce();
    }
    
    if (tagA == GlobalParams::Instance().TagMap["KeyPhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player hold Key");
        KeyToNextstage::onContactWithPlayer(physicsBodyA);
        currentPlayer->setHoldKey();
    } else if (tagB == GlobalParams::Instance().TagMap["KeyPhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player hold Key");
        KeyToNextstage::onContactWithPlayer(physicsBodyB);
        currentPlayer->setHoldKey();
    }

    if (tagA == GlobalParams::Instance().TagMap["DestinationPointPhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        if (currentPlayer->getHoldKeyStatus()) {
            // next stage
            currentDestinationPoint->onContactWithPlayer();
            if (this->StageNumber < GlobalParams::Instance().TotalStagesCount) {
                auto scene = GamePlayingScene::createScene(++StageNumber);
                Director::getInstance()->replaceScene(scene);
            } else {
                auto scene = CreditScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        }
    } else if (tagB == GlobalParams::Instance().TagMap["DestinationPointPhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        if (currentPlayer->getHoldKeyStatus()) {
            // next stage
            currentDestinationPoint->onContactWithPlayer();
            if (this->StageNumber < GlobalParams::Instance().TotalStagesCount) {
				log("Perform Segue While DestPoint");
                auto scene = GamePlayingScene::createScene(++StageNumber);
                Director::getInstance()->replaceScene(scene);
            } else {
				log("Perform Segue While DestPoint");
                auto scene = CreditScene::createScene();
                Director::getInstance()->replaceScene(scene);
            }
        }
    }
    
    if (tagA == GlobalParams::Instance().TagMap["TurtlePhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player collide Turtle");
        FlyingTurtle::onContactWithPlayer(physicsBodyA, currentPlayer);
		log("player isDead? [%d]", (int)currentPlayer->isDead());
        if (currentPlayer->isDead()) {
			log("Perform Segue While Turtle");
            auto scene = GamePlayingScene::createScene(StageNumber, false);
            Director::getInstance()->replaceScene(scene);
        }
    } else if (tagB == GlobalParams::Instance().TagMap["TurtlePhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player collide Turtle");
        FlyingTurtle::onContactWithPlayer(physicsBodyB, currentPlayer);
        if (currentPlayer->isDead()) {
			log("Perform Segue While Turtle");
            auto scene = GamePlayingScene::createScene(StageNumber, false);
            Director::getInstance()->replaceScene(scene);
        }
    }
    
    if (tagA == GlobalParams::Instance().TagMap["GearPhysics"] && tagB == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player collide Gear");
        Gear::onContactWithPlayer(currentPlayer);
        if (currentPlayer->isDead()) {
			log("Perform Segue While Gear/Spike");
            auto scene = GamePlayingScene::createScene(StageNumber, false);
            Director::getInstance()->replaceScene(scene);
        }
    } else if (tagB == GlobalParams::Instance().TagMap["GearPhysics"] && tagA == GlobalParams::Instance().TagMap["PlayerPhysics"]) {
        log("Player collide Gear");
        Gear::onContactWithPlayer(currentPlayer);
        if (currentPlayer->isDead()) {
			log("Perform Segue While Gear/Spike");
            auto scene = GamePlayingScene::createScene(StageNumber, false);
            Director::getInstance()->replaceScene(scene);
        }
    }
    
    return true;
}

void GamePlayingScene::backButtonCallback(cocos2d::Ref *pSender) {
    log("back Button clicked From StageSelect Scene");
    log("back Button : From StageSelect Scene To StartScene");
    auto * scene = StageSelectScene::createScene();
    Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5f, scene));
}

void GamePlayingScene::muteButtonCallBack(Ref* pSender, cocos2d::Label *muteLabel) {
	GlobalParams::Instance().Mute = !(GlobalParams::Instance().Mute);
	if (GlobalParams::Instance().Mute) {
		muteLabel->setTextColor(Color4B(30, 30, 30, 255));
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		muteLabel->setTextColor(Color4B(150, 150, 150, 255));
		SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM/SMBSM3DL_4.mp3", true);
	}
}
