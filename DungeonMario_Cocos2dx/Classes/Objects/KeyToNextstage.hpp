//
//  KeyToNextstage.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef KeyToNextstage_hpp
#define KeyToNextstage_hpp

#include "RawObject.hpp"
#include "cocos2d.h"
USING_NS_CC;

class KeyToNextstage : public RawObject {
    
public:
    void update() {}
    void updatePerSec() {}
    
    KeyToNextstage() {
        initSprite();
    }
    
    void initSprite();
    void startPlaying();
    static void onContactWithPlayer(cocos2d::PhysicsBody* key);
    
};

#endif /* KeyToNextstage_hpp */
