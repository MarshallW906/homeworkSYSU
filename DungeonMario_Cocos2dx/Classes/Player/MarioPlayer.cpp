//
//  MarioPlayer.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#include "MarioPlayer.hpp"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


void MarioPlayer::initSprite() {
    auto texture = Director::getInstance()->getTextureCache()->addImage("ObjectPics/MarioBig.png");
    idleRight = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 32, 32)));
    runRight = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 32, 32, 32)));
    idleLeft = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 64, 32, 32)));
    runLeft = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 96, 32, 32)));
    
    playerSprite = Sprite::createWithSpriteFrame(idleRight);
    playerSprite->setName("Player");
    playerSprite->setTag(GlobalParams::Instance().TagMap["Player"]);
    
    playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.5f));
    
    playerPhysicsBody->setCategoryBitmask(0xFFFFFFFF);
    playerPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    playerPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    playerPhysicsBody->setRotationEnable(false);
    playerPhysicsBody->setDynamic(true);
    playerPhysicsBody->setName("PlayerPhysics");
    playerPhysicsBody->setGravityEnable(true);
    getPlayerPhysicsBody()->setTag(GlobalParams::Instance().TagMap["PlayerPhysics"]);
    
    playerSprite->setPhysicsBody(playerPhysicsBody);
}

void MarioPlayer::update() {
    // move
    auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    if(GlobalParams::Instance().isKeyPressed(leftArrow)) {
        move(leftArrow);
    } else if(GlobalParams::Instance().isKeyPressed(rightArrow)) {
        move(rightArrow);
	}
}

void MarioPlayer::updatePerSec() {
    if (invisibleTime > 0) {
        invisibleTime--;
    }
	/*
	if (!GlobalParams::Instance().isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) && !GlobalParams::Instance().isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		if (isMoving == 1) {
			this->playerSprite->setSpriteFrame(idleLeft);
		} else if (isMoving == 2) {
			this->playerSprite->setSpriteFrame(idleRight);
		}
		isMoving = 0;
	}
	*/
}

void MarioPlayer::setInvisible() {
    this->invisibleTime = 5;
}
void MarioPlayer::setImmunityOnce() {
    this->immunityOnce = true;
}
void MarioPlayer::setNoImmunity() {
	this->immunityOnce = false;
}
void MarioPlayer::setHoldKey() {
    isHoldKey = true;
}
void MarioPlayer::getHurt() {
    if (this->immunityOnce) {
		this->immunityOnce = false;
    } else {
        isGoDie = true;
    }
}
bool MarioPlayer::isDead() {
    return isGoDie;
}
bool MarioPlayer::getHoldKeyStatus() {
    return isHoldKey;
}

void MarioPlayer::jump() {
    if (isJumping < 2) {
        isJumping++;
        playerPhysicsBody->setVelocity(Vec2(0, 250));
		if (!GlobalParams::Instance().Mute) {
			SimpleAudioEngine::getInstance()->playEffect("mp3/Effect/jump.mp3");
		}
    }
}
void MarioPlayer::move(EventKeyboard::KeyCode code) {
    int offsetX = 0, offsetY = 0;
    switch (code) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (!playerSprite->isFlippedX()) {
				playerSprite->setFlippedX(true);
			}
            offsetX = -moveSpeed;
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (playerSprite->isFlippedX()) {
				playerSprite->setFlippedX(false);
			}
            offsetX = moveSpeed;
            break;
        default:
            offsetY = offsetX = 0;
            break;
    }
    getPlayerSprite()->runAction(MoveTo::create(0.3f, Vec2(getPlayerSprite()->getPositionX() + offsetX, getPlayerSprite()->getPositionY() + offsetY)));
}

void MarioPlayer::onCollisionWithMap() {
    isJumping = 0;
}

void MarioPlayer::onCollisionWithEnemy() {
    // GameOver
}
