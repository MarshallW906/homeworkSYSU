//
//  Mushroom.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#ifndef Mushroom_hpp
#define Mushroom_hpp

#include "RawObject.hpp"

class Mushroom : public RawObject {
    
public:
    void update() {}
    void updatePerSec() {}
    
    Mushroom() {
        initSprite();
    }
    
    void initSprite();
    void startPlaying();
    static void onContactWithPlayer(PhysicsBody* mushroom);
};

#endif /* Mushroom_hpp */
