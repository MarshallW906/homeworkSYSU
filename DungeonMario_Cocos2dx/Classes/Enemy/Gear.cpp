//
//  Gear.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#include "Gear.hpp"
#include "GlobalParams.hpp"

void Gear::initSprite() {
    auto gearFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("spike-0.bmp");
    relatedSprite = Sprite::createWithSpriteFrame(gearFrame1);
    relatedSprite->setName("Gear");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Gear"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(1.0, 1.0, 1.0));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["GearPhysics"]);
    relatedPhysicsBody->setName("GearPhysics");
    relatedPhysicsBody->setCategoryBitmask(0x0000FF00);
    relatedPhysicsBody->setCollisionBitmask(0x000000FF);
    relatedPhysicsBody->setContactTestBitmask(0x0000FFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
    
    relatedSprite->setScale(0.5f, 0.5f);
    
    relatedSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("spikeAnimation"))));
}

void Gear::startPlaying() {
    // create an [Animate Sequence] and make it repeat forever
    return;
}

void Gear::onContactWithPlayer(MarioPlayer* player) {
    /**
     * get Player Instance from GlobalParams::Instance()
     *
     * judge : if stepped by Player => go die
     *         if just collision => player go die, restart
     */
    player->getHurt();
}
