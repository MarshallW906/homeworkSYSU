//
//  GamePlayingScene.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//

#ifndef __GamePlayingScene_SCENE_H__
#define __GamePlayingScene_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Player/MarioPlayer.hpp"
#include "RawObject.hpp"
// Enemy
#include "Enemy/FlyingTurtle.hpp"
#include "Enemy/Gear.hpp"
#include "Enemy/ChestnutMon.hpp"
// Object
#include "Objects/Tanhuang.hpp"
#include "Objects/DestinationPoint.hpp"
#include "Objects/StartPoint.hpp"
#include "Objects/Mushroom.hpp"
#include "Objects/KeyToNextstage.hpp"
#include "Objects/IceRock.hpp"
#include "Objects/FlyingPlatform.hpp"
#include "Objects/Coin.hpp"
#include "Objects/PlainRock.hpp"


class GamePlayingScene : public cocos2d::Scene
{
private:
    PhysicsWorld* m_world;
    TMXTiledMap *currentStageTmx;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    int currentTimeCount;
    
    MarioPlayer *currentPlayer;
    // map rocks
    std::list<PlainRock> currentPlainRocks;
    std::list<IceRock> currentIceRocks;
    // Objects
    StartPoint* currentStartPoint;
    DestinationPoint* currentDestinationPoint;
    KeyToNextstage* currentKey;
    std::list<Mushroom> currentMushrooms;
    std::list<Coin> currentCoins;
    std::list<FlyingPlatform> currentFlyingPlatforms;
    std::list<Tanhuang> currentTanhuangs;
    // Enemy
    std::vector<FlyingTurtle> currentTurtles;
    std::vector<ChestnutMon> currentChestnuts;
    std::vector<Gear> currentGears;

public:
    static cocos2d::Scene* createScene(int currentStageNumber, bool changeBGM);
    virtual bool init(int currentStageNumber, bool changeBGM);
    
    static PhysicsWorld* world;
    void setPhysicsWorld(PhysicsWorld * world);
    
    int StageNumber;
    
    // implement the "static create()" method manually
    static GamePlayingScene * create(int currentStageNumber = 1, bool changeBGM = true) {
        GamePlayingScene *pRet = new(std::nothrow) GamePlayingScene();
        if (pRet && pRet->init(currentStageNumber, changeBGM)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    
    void loadMap();
    void addHUD();
    void addPlayer();
    void addListener();
    void loadMusic(bool changeBGM);
    void loadAnimation(std::string filepath);
    
    void loadStage1();
    void loadStage2();
    void loadStage3();
    
    void releaseObjects();
    
    void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
    bool onContactBegin(PhysicsContact & contact);
    
    void update(float dt);
    void updatePerSec(float dt);
    
    void backButtonCallback(cocos2d::Ref* pSender);
	void muteButtonCallBack(Ref* pSender, cocos2d::Label *muteLabel);
    
    ~GamePlayingScene() {
        releaseObjects();
    }
};


#endif /* __GamePlayingScene_SCENE_H__ */
