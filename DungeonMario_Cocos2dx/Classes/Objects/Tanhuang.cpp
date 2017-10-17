//
//  Tanhuang.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "Tanhuang.hpp"
#include "GlobalParams.hpp"
#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void Tanhuang::initSprite() {
    /**
     * create with pics
     * get Tanhuang's locations and get one
     * set collisionBitmask, categoryBitmask, contactTestBitmask
     * associate PhysicsBody with the Sprite
     * [Set Position AT THE OUTER CODE]
     */
    auto tanhuangFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Tanhuang.png");
    relatedSprite = Sprite::createWithSpriteFrame(tanhuangFrame);
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Tanhuang"]);
    relatedSprite->setName("Tanhuang");
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(5.0, 0.0, 1.0f));
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["TanhuangPhysics"]);
    relatedPhysicsBody->setName("TanhuangPhysics");
    relatedPhysicsBody->setCategoryBitmask(0xFF000000);
    relatedPhysicsBody->setCollisionBitmask(0x00FF0000);
    relatedPhysicsBody->setContactTestBitmask(0xFFFF0000);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
}

void Tanhuang::onContactWithPlayer(cocos2d::PhysicsBody* tanhuang, cocos2d::Sprite* marioPlayerSprite) {
    marioPlayerSprite->getPhysicsBody()->setVelocity(Vec2(0, 400));
	if (!GlobalParams::Instance().Mute) {
		SimpleAudioEngine::getInstance()->playEffect("mp3/Effect/spring.mp3");
	}
}
