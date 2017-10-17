//
//  KeyToNextstage.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "KeyToNextstage.hpp"
#include "GlobalParams.hpp"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void KeyToNextstage::initSprite() {
    auto keyFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("key-0.png");
    relatedSprite = Sprite::createWithSpriteFrame(keyFrame1);
    relatedSprite->setName("Key");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Key"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(0.1, 0.0, 0.0f));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["KeyPhysics"]);
    relatedPhysicsBody->setName("KeyPhysics");
    relatedPhysicsBody->setCategoryBitmask(0x0000FF00);
    relatedPhysicsBody->setCollisionBitmask(0x000000FF);
    relatedPhysicsBody->setContactTestBitmask(0x0000FFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
    
    relatedSprite->setScale(0.2f, 0.2f);
    
    relatedSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("keyAnimation"))));
}

void KeyToNextstage::startPlaying() {
}

void KeyToNextstage::onContactWithPlayer(cocos2d::PhysicsBody* key) {
    key->getOwner()->removeFromParent();
	if (!GlobalParams::Instance().Mute) {
		SimpleAudioEngine::getInstance()->playEffect("mp3/Effect/coin.mp3");
	}
}


