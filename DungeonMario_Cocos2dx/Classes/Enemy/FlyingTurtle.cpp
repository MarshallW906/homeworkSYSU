//
//  FlyingTurtle.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//

#include "FlyingTurtle.hpp"
#include "GlobalParams.hpp"
#include "Player/MarioPlayer.hpp"


void FlyingTurtle::initSprite() {
    auto TurtleIdleLeftAnimation = AnimationCache::getInstance()->getAnimation("TurtleIdleLeftAnimation");
    relatedSprite = Sprite::createWithSpriteFrame(TurtleIdleLeftAnimation->getFrames().at(0)->getSpriteFrame());
    
    relatedSprite->setName("Turtle");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["Turtle"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(1.0, 1.0, 1.0f));
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["TurtlePhysics"]);
    relatedPhysicsBody->setName("TurtlePhysics");
    relatedPhysicsBody->setCategoryBitmask(0xFFFFFFF);
    relatedPhysicsBody->setCollisionBitmask(0xFFFFFFFF);
    relatedPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
    
    relatedSprite->setScale(0.5f, 0.5f);
    
    relatedSprite->runAction(RepeatForever::create(Animate::create(TurtleIdleLeftAnimation)));
}

void FlyingTurtle::startPlaying() {
    // create an [Animate Sequence] and make it repeat forever
    auto moveUp = MoveBy::create(1.5f, Vec2(0, 30));
    auto moveDown = MoveBy::create(1.5f, Vec2(0, -30));
    auto patrolAction = Sequence::create(moveUp, moveDown, NULL);
    relatedSprite->runAction(RepeatForever::create(patrolAction));
}

void FlyingTurtle::onContactWithPlayer(PhysicsBody* turtle, MarioPlayer* player) {
    log("Turtle Contact With Player");
    auto turtleBoundingBox = turtle->getOwner()->getBoundingBox();
    auto playerBoundingBox = player->getPlayerSprite()->getBoundingBox();
    
    if (turtleBoundingBox.getMaxY() <= playerBoundingBox.getMinY() + 5) {
		log("turtle STEPPED BY player");
		turtle->getOwner()->removeFromParentAndCleanup(true);
	} else {
		log("turtle HURT player");
        player->getHurt();
    }
}
