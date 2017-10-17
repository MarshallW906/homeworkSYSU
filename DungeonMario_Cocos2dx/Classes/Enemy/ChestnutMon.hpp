//
//  ChestnutMon.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef ChestnutMon_hpp
#define ChestnutMon_hpp

#include "RawObject.hpp"
#include "Player/MarioPlayer.hpp"
#include "cocos2d.h"
USING_NS_CC;

class ChestnutMon : public RawObject {
    float moveSpeed;
    
public:
    ChestnutMon () {
        initSprite();
    }
    
    void initSprite();
    void startPlaying();
    static void onContactWithPlayer(PhysicsBody* chestnut, MarioPlayer* player);
    void update() {}
    void updatePerSec() {}
};

#endif /* ChestnutMon_hpp */
