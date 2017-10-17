//
//  MarioPlayer.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#ifndef MarioPlayer_hpp
#define MarioPlayer_hpp

#include "cocos2d.h"
USING_NS_CC;

#include "GlobalParams.hpp"

class MarioPlayer {
    
    float moveSpeed;
    int isJumping;
    // invisibleTime > 0 => Be Invisible; invisibleTime-- each second
	int invisibleTime;
	bool immunityOnce;
	bool isHoldKey;
	bool isGoDie;
	int isMoving;
    
    // cocos2d::Sprite
    cocos2d::Sprite* playerSprite;
    cocos2d::PhysicsBody* playerPhysicsBody;
    SpriteFrame* idleRight, *runRight, *idleLeft, *runLeft;
    
public:
    MarioPlayer () {
        moveSpeed = GlobalParams::Instance().playerMoveSpeed;
        isJumping = 0;
        invisibleTime = 0;
        isHoldKey = false;
		immunityOnce = false;
		isGoDie = false;
		isMoving = 0;

        initSprite();
    }
    
    void initSprite();
    void update();
    void updatePerSec();
    
    // status settings
    void setInvisible();
    void setImmunityOnce();
    void setNoImmunity();
    void setHoldKey();
    bool getHoldKeyStatus();
    void getHurt();
    bool isDead();
    
    // acitons
    void jump();
    void move(EventKeyboard::KeyCode code);
    
    void onCollisionWithMap();
    void onCollisionWithEnemy();

    cocos2d::Sprite* getPlayerSprite() {
        return playerSprite;
    }
    cocos2d::PhysicsBody* getPlayerPhysicsBody() {
        return playerPhysicsBody;
    }
    
};

#endif /* MarioPlayer_hpp */
