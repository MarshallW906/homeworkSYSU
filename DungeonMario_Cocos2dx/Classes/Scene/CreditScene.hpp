//
//  CreditScene.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//


#ifndef __CreditScene_SCENE_H__
#define __CreditScene_SCENE_H__

#include "cocos2d.h"

class CreditScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void backButtonCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CreditScene);
};

#endif // __CreditScene_SCENE_H__
