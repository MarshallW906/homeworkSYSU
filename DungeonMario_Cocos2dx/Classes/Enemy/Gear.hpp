//
//  Gear.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#ifndef Gear_hpp
#define Gear_hpp

#include "RawObject.hpp"
#include "GlobalParams.hpp"
#include "Player/MarioPlayer.hpp"

#include "cocos2d.h"
USING_NS_CC;

class Gear : public RawObject {
public:
    Gear () {
        initSprite();
    }
    // inherited
    void initSprite();
    void update() {}
    void updatePerSec() {}
    
    void startPlaying();
    static void onContactWithPlayer(MarioPlayer* player);
    
};


#endif /* Gear_hpp */
