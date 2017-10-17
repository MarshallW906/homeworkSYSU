//
//  PlainRock.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/9.
//
//

#ifndef PlainRock_hpp
#define PlainRock_hpp

#include "RawObject.hpp"
#include "cocos2d.h"
USING_NS_CC;

class PlainRock : public RawObject {
    Vector<SpriteFrame*> rockFrames;
    
public:
    PlainRock() {
        initSprite();
    }
    
    void startPlaying() {}
    void update() {}
    void updatePerSec();
    
    void initSprite();
    static void onContactWithPlayer(cocos2d::PhysicsBody* theRock);

};

#endif /* PlainRock_hpp */
