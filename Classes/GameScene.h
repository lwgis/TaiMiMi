//
//  GameScene.h
//  TaiMiMi
//
//  Created by 李炜 on 14-4-13.
//
//

#ifndef __TaiMiMi__GameScene__
#define __TaiMiMi__GameScene__

#include "cocos2d.h"
#include "MiMiSprite.h"
#include "PipeSprite.h"
USING_NS_CC;
class GameScene:public cocos2d::Layer{
private:
	Sprite* landSprite1;
	Sprite* landSprite2;
	float adjustmentBg;
	MiMiSprite *mimiSprite;
	Vector<PipeSprite*> allPipeSprite;
	LabelAtlas *lableScore;
	int Score;
public:
	 virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
	void update(float dt);
	void startGame();
	void endGame();
	void createPipe(float dt);
	void collisionDetection(float dt);
	void reStartGame(cocos2d::Ref *pSender);


};

#endif /* defined(__TaiMiMi__GameScene__) */
