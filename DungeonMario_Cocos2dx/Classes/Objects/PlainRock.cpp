//
//  PlainRock.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/9.
//
//

#include "PlainRock.hpp"

#include "GlobalParams.hpp"

void PlainRock::initSprite() {
    auto plainRockTexture = Director::getInstance()->getTextureCache()->addImage("ObjectPics/PlainRock.png");

    for (int i = 0; i < 6; i++) {
        auto frame = SpriteFrame::createWithTexture(plainRockTexture, CC_RECT_PIXELS_TO_POINTS(Rect(0, i * 32, 32, 32)));
        rockFrames.pushBack(frame);
    }
    relatedSprite = Sprite::createWithSpriteFrame(rockFrames.at(0));
    relatedSprite->setName("PlainRock");
    relatedSprite->setTag(GlobalParams::Instance().TagMap["PlainRock"]);
    
    relatedPhysicsBody = PhysicsBody::createBox(relatedSprite->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.5f));
    relatedPhysicsBody->setDynamic(false);
    relatedPhysicsBody->setGravityEnable(false);
    relatedPhysicsBody->setName("PlainRockPhysics");
    relatedPhysicsBody->setTag(GlobalParams::Instance().TagMap["PlainRockPhysics"]);
    relatedPhysicsBody->setCategoryBitmask(0xFF000000);
    relatedPhysicsBody->setCollisionBitmask(0x00FF0000);
    relatedPhysicsBody->setContactTestBitmask(0xFFFF0000);
    
    relatedSprite->setPhysicsBody(relatedPhysicsBody);
}

void PlainRock::updatePerSec() {
    static int timeCount = 0;
    if (++timeCount % 10 == 0) {
        int i = random(0, 5);
        std::stringstream ss;
        ss << "PlainRock-" << i << ".png";
        relatedSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
    }
}

void PlainRock::onContactWithPlayer(cocos2d::PhysicsBody* theRock) {
    
}
