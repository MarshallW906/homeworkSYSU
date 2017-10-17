//
//  Tanhuang.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef Tanhuang_hpp
#define Tanhuang_hpp

#include "RawObject.hpp"

#include "cocos2d.h"
USING_NS_CC;

class Tanhuang : public RawObject {
    
public:
    Tanhuang () {
        initSprite();
    }
    
    void update() {}
    void updatePerSec() {}
    void startPlaying() {}
    
    void initSprite();
    static void onContactWithPlayer(cocos2d::PhysicsBody* tanhuang, cocos2d::Sprite* marioPlayerSprite);
};

#endif /* Tanhuang_hpp */
