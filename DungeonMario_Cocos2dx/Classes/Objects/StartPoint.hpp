//
//  StartPoint.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef StartPoint_hpp
#define StartPoint_hpp

#include "RawObject.hpp"

#include "cocos2d.h"
USING_NS_CC;

class StartPoint : public RawObject {
    
public:
    StartPoint () {
        initSprite();
    }
    ~StartPoint() {}
    
    void update() {return;}
    void updatePerSec() {return;}
    
    void initSprite();
    void startPlaying();
    void onContactWithPlayer();
};

#endif /* StartPoint_hpp */
