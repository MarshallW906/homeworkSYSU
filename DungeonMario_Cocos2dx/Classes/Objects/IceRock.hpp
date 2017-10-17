//
//  IceRock.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef IceRock_hpp
#define IceRock_hpp

#include "RawObject.hpp"
#include "cocos2d.h"
USING_NS_CC;

class IceRock : public RawObject {
    
public:
    IceRock() {
        initSprite();
    }
    
    void startPlaying() {}
    void update() {}
    void updatePerSec() {}
    
    void initSprite();
    static void onContactWithPlayer(cocos2d::PhysicsBody* theRock);
};

#endif /* IceRock_hpp */
