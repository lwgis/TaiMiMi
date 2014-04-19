//
//  StartScene.cpp
//  TaiMiMi
//
//  Created by 李炜 on 14-4-13.
//
//

#include "StartScene.h"
#include "cocos2d.h"
#include "GameScene.h"
#include <string>
#include <Box2D/Box2D.h>
bool StartScene::init(){
	if (!Layer::init()) {
		return false;
	}
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("startScene.plist");
	batchNode=SpriteBatchNode::create("startScene.pvr.ccz");
	addChild(batchNode);
	Size winSize=Director::getInstance()->getVisibleSize();
	//背景
	auto bgSprite=Sprite::createWithSpriteFrameName("backgroud.png");
	bgSprite->setAnchorPoint(Point(0,0));
	batchNode->addChild(bgSprite);
	//游戏名称
	auto gameNameSprite=Sprite::createWithSpriteFrameName("gameName.png");
	gameNameSprite->setPosition(winSize.width/2, winSize.height-200);
	batchNode->addChild(gameNameSprite);
	//摇头
	//auto mimiSprite=Sprite::create("mimi1.png");
	//mimiSprite->setPosition(winSize.width/2,winSize.height-300);
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mimi.plist");
	//Vector<SpriteFrame*> listArray;
	////auto listArray=Array::createWithCapacity(4);
	//for (int i = 1; i < 5; i++)
	//{
	//	const char* img_name = String::createWithFormat("mimi%d.png", i)->getCString();
	//	listArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(img_name));
	//}
	//auto anim=Animation::createWithSpriteFrames(listArray,0.2);
	//auto animate = Animate ::create(anim);
	//auto act=RepeatForever::create(animate);
	//mimiSprite->runAction(act);
	//this->addChild(mimiSprite);
	auto mimiSprite=Sprite::createWithSpriteFrameName("mimiStart.png");
	mimiSprite->setPosition(60,147);
	auto jump=JumpBy::create(2,Point(winSize.width/2,320),500,1);
	auto sequence=Sequence::create(jump,jump->reverse(),nullptr);
	auto rotate=RotateBy::create(2,360.0f);
	auto spawn=Spawn::create(sequence,rotate,nullptr);
	auto repeat=RepeatForever::create(spawn);
	mimiSprite->runAction(repeat);
	batchNode->addChild(mimiSprite);
	//地面
	this->landSprite1=Sprite::createWithSpriteFrameName("land.png");
	this->landSprite2=Sprite::createWithSpriteFrameName("land.png");

	landSprite1->setAnchorPoint(Point(0,0));
	landSprite2->setAnchorPoint(Point(0,0));
	landSprite2->setPosition(Point(winSize.width,0));
//    bgSprite->setPosition(Point(winSize.width/2,winSize.height/2));
	batchNode->addChild(this->landSprite1);
	batchNode->addChild(this->landSprite2);
	this->scheduleUpdate();
//    this->schedule(schedule_selector(StartScene::move), 1/240.0);
	auto startButton=MenuItemImage::create("startButton.png", "startButton.png",CC_CALLBACK_1(StartScene::startGame, this));
	auto menu=Menu::create(startButton, NULL);
	menu->setPosition(winSize.width/2, 300);
	this->addChild(menu);
	return true;
}

void StartScene::startGame(cocos2d::Ref *pSender){
	TransitionScene *trans=TransitionFade::create(1, GameScene::createScene());
	Director::getInstance()->replaceScene(trans);
}


Scene* StartScene::createScene(){
	auto scene=Scene::create();
	auto layer=StartScene::create();
	scene->addChild(layer);
	return scene;
	
}
void StartScene::update(float dt){
	Size winSize=Director::getInstance()->getVisibleSize();
	adjustmentBg-=5;
	if (adjustmentBg<=0) {
		adjustmentBg=winSize.width;
	}
	landSprite1->setPosition(Point(adjustmentBg-winSize.width,landSprite1->getPosition().y));
	landSprite2->setPosition(Point(adjustmentBg,landSprite2->getPosition().y));

//    [landSprite1 setPosition:ccp(adjustmentBG-320, landSprite1.position.y)];
//    [landSprite2 setPosition:ccp(adjustmentBG, landSprite2.position.y)];

}
StartScene::~StartScene(){
	//delete word;
}



