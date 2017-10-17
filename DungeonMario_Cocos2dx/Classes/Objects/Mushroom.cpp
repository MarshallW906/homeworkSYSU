//
//  Mushroom.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "Mushroom.hpp"
#include "GlobalParams.hpp"

#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void Mushroom::initSprite() {
    auto mushroomFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Mushroom.png");
    relatedSprite = Sprite::createWithSpriteFrame(mushroomFrame);
    relatedSprite->setName("Mushroom");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Mushroom"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["MushroomPhysics"]);
    relatedPhysicsBody->setName("MushroomPhysics");
    relatedPhysicsBody->setCategoryBitmask(0x0000FF00);
    relatedPhysicsBody->setCollisionBitmask(0x000000FF);
    relatedPhysicsBody->setContactTestBitmask(0x0000FFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
}

void Mushroom::startPlaying() {

}

void Mushroom::onContactWithPlayer(cocos2d::PhysicsBody* mushroom) {
    mushroom->getOwner()->removeFromParent();
	if (!GlobalParams::Instance().Mute) {
		SimpleAudioEngine::getInstance()->playEffect("mp3/Effect/1up.mp3");
	}
}
