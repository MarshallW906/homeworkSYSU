//
//  IceRock.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "IceRock.hpp"
#include "GlobalParams.hpp"

void IceRock::initSprite() {
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("IceRock.png");
    relatedSprite = Sprite::createWithSpriteFrame(frame);
    relatedSprite->setName("IceRock");
//    relatedSprite->setScale(<#float scaleX#>, <#float scaleY#>);
    relatedSprite->setTag(GlobalParams::Instance().TagMap["IceRock"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
    relatedPhysicsBody->setName("IceRockPhysics");
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["IceRockPhysics"]);
    relatedPhysicsBody->setCategoryBitmask(0xFF000000);
    relatedPhysicsBody->setCollisionBitmask(0x00FF0000);
    relatedPhysicsBody->setContactTestBitmask(0xFFFF0000);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
}

void IceRock::onContactWithPlayer(cocos2d::PhysicsBody* theRock) {

}
