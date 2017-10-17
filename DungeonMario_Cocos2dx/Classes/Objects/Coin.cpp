//
//  Coin.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "Coin.hpp"
#include "GlobalParams.hpp"

void Coin::initSprite() {
    auto coinFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin-0.png");
    relatedSprite = Sprite::createWithSpriteFrame(coinFrame1);
    relatedSprite->setName("Coin");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Coin"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(0.1, 0.0, 0.0f));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["CoinPhysics"]);
    relatedPhysicsBody->setName("CoinPhysics");
    relatedPhysicsBody->setCategoryBitmask(0x0000FF00);
    relatedPhysicsBody->setCollisionBitmask(0x000000FF);
    relatedPhysicsBody->setContactTestBitmask(0x0000FFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
    
    relatedSprite->setScale(1.0f, 1.0f);
    
    relatedSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("coinAnimation"))));
}

void Coin::onContactWithPlayer(cocos2d::PhysicsBody *coin) {
    coin->getOwner()->removeFromParent();
}
