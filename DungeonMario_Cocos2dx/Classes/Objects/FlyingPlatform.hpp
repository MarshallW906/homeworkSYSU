//
//  FlyingPlatform.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef FlyingPlatform_hpp
#define FlyingPlatform_hpp

#include "RawObject.hpp"
#include "cocos2d.h"
USING_NS_CC;

class FlyingPlatform : public RawObject {
    cocos2d::Vec2 endPointInTmux;
    
public:
    FlyingPlatform() {
        initSprite();
    }
    
    void update();
    void updatePerSec();
    
    void initSprite();
    void startPlaying();
    static void onContactWithPlayer(cocos2d::PhysicsBody* platform);
};

#endif /* FlyingPlatform_hpp */
