//
//  RawObject.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#ifndef RawObject_hpp
#define RawObject_hpp

#include "cocos2d.h"
USING_NS_CC;

class RawObject {
protected:
    RawObject() {}
    ~RawObject() {}
    bool isRunning = true;
    cocos2d::Sprite* relatedSprite;
    PhysicsBody* relatedPhysicsBody;
    cocos2d::Vec2 locationInTmux;
    
public:
    virtual void initSprite() = 0;
    
    virtual void update() = 0;
    virtual void updatePerSec() = 0;
    
    cocos2d::Vec2 getPositionInTmux();
    void setPositionInTmux(cocos2d::Vec2);
    
    cocos2d::PhysicsBody* getRelatedPhysicsBody();
    void setRelatedPhysicsBody(cocos2d::PhysicsBody* pbody);
    
    cocos2d::Sprite* getRelatedCCSprite();
    
    virtual void startPlaying() = 0;
    void setRunningEnable();
    void setRunningDisable();
    
    void setPosition(cocos2d::Vec2);
};

#endif /* RawObject_hpp */
