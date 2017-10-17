//
//  GlobalParams.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#ifndef GlobalParams_hpp
#define GlobalParams_hpp

#include "cocos2d.h"
USING_NS_CC;

class GlobalParams {
public:
    static GlobalParams& Instance() {
        static GlobalParams theSingleton;
        return theSingleton;
    }
    
    /* more (non-static) functions here */
    float gearRadius;
    float enemyPatrolSpeed;
    float playerMoveSpeed;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    bool isKeyPressed(EventKeyboard::KeyCode code);
    std::map<std::string, int> TagMap;
    int TotalStagesCount;
	bool Mute;
    
private:
    // ctor hidden
    GlobalParams();
     // copy ctor hidden
    GlobalParams(GlobalParams const&);
    // assign op. hidden
    GlobalParams & operator=(GlobalParams const&);
    // dtor hidden
    ~GlobalParams() {}
};

#endif /* GlobalParams_hpp */
