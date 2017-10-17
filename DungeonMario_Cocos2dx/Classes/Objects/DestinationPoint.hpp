//
//  DestinationPoint.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef DestinationPoint_hpp
#define DestinationPoint_hpp

#include "RawObject.hpp"

#include "cocos2d.h"
USING_NS_CC;

class DestinationPoint : public RawObject {
    
public:
    DestinationPoint () {
        initSprite();
    }
    
    void update() {}
    void updatePerSec() {}
    
    void initSprite();
    void startPlaying();
    void onContactWithPlayer();
};

#endif /* DestinationPoint_hpp */
