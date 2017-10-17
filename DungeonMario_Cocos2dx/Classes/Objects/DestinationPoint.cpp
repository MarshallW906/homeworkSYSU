//
//  DestinationPoint.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "DestinationPoint.hpp"
#include "GlobalParams.hpp"

#include "cocos2d.h"
USING_NS_CC;

void DestinationPoint::initSprite() {
    /**
     * create with pics
     * get the location
     * set collisionBitmask, categoryBitmask, contactTestBitmask
     * associate PhysicsBody with the Sprite
     * [Set Position AT THE OUTER CODE]
     */
    auto destinationFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("DestinationPoint.png");
    relatedSprite = Sprite::createWithSpriteFrame(destinationFrame);
    relatedSprite->setTag(GlobalParams::Instance().TagMap["DestinationPoint"]);
    relatedSprite->setName("DestinationPoint");
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(0.1, 0.0, 1.0f));
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["DestinationPointPhysics"]);
    relatedPhysicsBody->setName("DestinationPointPhysics");
    relatedPhysicsBody->setCategoryBitmask(0xFF000000);
    relatedPhysicsBody->setCollisionBitmask(0x00FF0000);
    relatedPhysicsBody->setContactTestBitmask(0xFFFF0000);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
}

void DestinationPoint::onContactWithPlayer() {
    log("Destination Point Arrived");
}

void DestinationPoint::startPlaying() {
    
}
