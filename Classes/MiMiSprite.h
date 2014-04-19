#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MiMiSprite :public cocos2d::Sprite
{
private:
	bool isUping;
	float g;
	float a;
	bool isStartGame;
public:
	static MiMiSprite *create();
	virtual bool initWithSpriteFrameName(const std::string& filename);
	virtual void update(float dt);
	void startGame();
	void endGame();
	void up();
	void upCallBack(Node *node);
};

