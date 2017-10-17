//
//  StageSelectScene.hpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/4.
//
//

#ifndef __StageSelectScene_SCENE_H__
#define __StageSelectScene_SCENE_H__

#include "cocos2d.h"

class StageSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void selectButtonCallBack(cocos2d::Ref* pSender, int stageNumber);
    void backButtonCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StageSelectScene);
};

#endif /* __StageSelectScene_SCENE_H__ */
