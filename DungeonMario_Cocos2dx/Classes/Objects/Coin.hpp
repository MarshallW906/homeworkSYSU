//
//  Coin.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef Coin_hpp
#define Coin_hpp

#include "RawObject.hpp"
#include "cocos2d.h"
USING_NS_CC;

class Coin : public RawObject {
    
public:
    Coin() {
        initSprite();
    }
    
    void initSprite();
    void startPlaying() {}
    static void onContactWithPlayer(PhysicsBody* coin);
    
    void update() {}
    void updatePerSec() {}
};

#endif /* Coin_hpp */
