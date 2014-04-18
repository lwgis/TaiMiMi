//
//  StartScene.h
//  TaiMiMi
//
//  Created by 李炜 on 14-4-13.
//
//

#ifndef __TaiMiMi__StartScene__
#define __TaiMiMi__StartScene__
#include "cocos2d.h"
USING_NS_CC;

class StartScene:public cocos2d::Layer{
private:
    Sprite* landSprite1;
    Sprite* landSprite2;
    float adjustmentBg;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
    void update(float dt);
    void startGame(cocos2d::Ref *pSender);
};
#endif /* defined(__TaiMiMi__StartScene__) */
