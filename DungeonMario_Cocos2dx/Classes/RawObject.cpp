//
//  RawObject.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#include "RawObject.hpp"

#include "cocos2d.h"
USING_NS_CC;

void RawObject::setRunningEnable() {
    this->isRunning = true;
}

void RawObject::setRunningDisable() {
    this->isRunning = false;
}


cocos2d::Vec2 RawObject::getPositionInTmux() {
    return locationInTmux;
}

void RawObject::setPositionInTmux(cocos2d::Vec2 targetVec) {
    this->locationInTmux = targetVec;
}


cocos2d::PhysicsBody* RawObject::getRelatedPhysicsBody() {
    return relatedPhysicsBody;
}

void RawObject::setRelatedPhysicsBody(cocos2d::PhysicsBody* pbody) {
    relatedSprite->setPhysicsBody(pbody);
    relatedPhysicsBody = pbody;
}

cocos2d::Sprite* RawObject::getRelatedCCSprite() {
    return relatedSprite;
}

void RawObject::setPosition(cocos2d::Vec2 position) {
    relatedSprite->setPosition(position);
}
