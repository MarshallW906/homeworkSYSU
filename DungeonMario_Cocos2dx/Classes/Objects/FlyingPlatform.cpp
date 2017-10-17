//
//  FlyingPlatform.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "FlyingPlatform.hpp"
#include "GlobalParams.hpp"

void FlyingPlatform::update() {
    
}
void FlyingPlatform::updatePerSec() {
    
}

void FlyingPlatform::initSprite() {
    auto keyFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("platform-0.png");
    relatedSprite = Sprite::createWithSpriteFrame(keyFrame1);
    relatedSprite->setName("FlyingPlatform");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["FlyingPlatform"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(0.1, 0.0, 0.0f));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["FlyingPlatformPhysics"]);
    relatedPhysicsBody->setName("FlyingPlatformPhysics");
    relatedPhysicsBody->setCategoryBitmask(0x0000FF00);
    relatedPhysicsBody->setCollisionBitmask(0x000000FF);
    relatedPhysicsBody->setContactTestBitmask(0x0000FFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
    
    relatedSprite->setScale(1.0f, 1.0f);
    
    relatedSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("platformAnimation"))));
}

void FlyingPlatform::startPlaying() {
    auto moveRight = MoveBy::create(1.5f, Vec2(20, 0));
    auto moveLeft = MoveBy::create(1.5f, Vec2(-20, 0));
    auto patrolAction = Sequence::create(moveRight, moveLeft, NULL);
    relatedSprite->runAction(RepeatForever::create(patrolAction));
}

void FlyingPlatform::onContactWithPlayer(cocos2d::PhysicsBody* platform) {

}
