//
//  FlyingTurtle.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#ifndef FlyingTurtle_hpp
#define FlyingTurtle_hpp

#include "RawObject.hpp"
#include "Player/MarioPlayer.hpp"

#include "cocos2d.h"
USING_NS_CC;

class FlyingTurtle : public RawObject {
    cocos2d::Vec2 endLocationInTmux;
    
public:
    FlyingTurtle () {
        initSprite();
    }
    
    void initSprite();
    void startPlaying();
    void update() {}
    void updatePerSec() {}
    
    static void onContactWithPlayer(PhysicsBody* turtle, MarioPlayer* player);
};

#endif /* FlyingTurtle_hpp */
