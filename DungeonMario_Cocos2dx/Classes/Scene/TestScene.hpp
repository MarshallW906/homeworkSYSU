//
//  TestScene.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//

#ifndef __TestScene_SCENE_H__
#define __TestScene_SCENE_H__

#include "cocos2d.h"

class TestScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene);
};

#endif // __TestScene_SCENE_H__
