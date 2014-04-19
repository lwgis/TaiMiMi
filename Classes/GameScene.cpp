//
//  GameScene.cpp
//  TaiMiMi
//
//  Created by 李炜 on 14-4-13.
//
//

#include "GameScene.h"
#include "StartScene.h"
#include <string.h>
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
bool GameScene::init(){
	if (!cocos2d::Layer::init()) {
		return false;
	}
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameScene.plist");
	batchNode=SpriteBatchNode::create("gameScene.pvr.ccz");
	addChild(batchNode);
	Size winSize=Director::getInstance()->getVisibleSize();
	auto bgSprite=Sprite::createWithSpriteFrameName("backgroud.png");//::create("backgroud.png");
	bgSprite->setAnchorPoint(Point(0,0));
	batchNode->addChild(bgSprite);
	//地面
	this->landSprite1=Sprite::createWithSpriteFrameName("land.png");
	this->landSprite2=Sprite::createWithSpriteFrameName("land.png");

	landSprite1->setAnchorPoint(Point(0,0));
	landSprite2->setAnchorPoint(Point(0,0));
	landSprite2->setPosition(Point(winSize.width,0));
//    bgSprite->setPosition(Point(winSize.width/2,winSize.height/2));
	batchNode->addChild(this->landSprite1,2);
	batchNode->addChild(this->landSprite2,2);
	this->mimiSprite=MiMiSprite::create();
	mimiSprite->setPosition( winSize.width*20/64,winSize.height/2);
	//mimiSprite->startGame();
	batchNode->addChild(mimiSprite,2);
	auto labelStart =LabelTTF::create("点击屏幕抬我","Marker Felt",58);//,Size::ZERO,TextHAlignment::CENTER,TextVAlignment::CENTER);
	labelStart->setPosition(winSize.width/2,winSize.height/3);

	this->addChild(labelStart);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();
	//如果不加入此句消息依旧会向下传递
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [=](Touch* touch,Event* event)
	{
		dispatcher->removeEventListener(myListener);
		labelStart->removeFromParentAndCleanup(true);
		this->startGame();
		this->mimiSprite->up();
		return true;
	};
dispatcher->addEventListenerWithSceneGraphPriority(myListener,this);
	this->scheduleUpdate();
	return true;
}

Scene * GameScene::createScene(){
	auto scene=Scene::create();
	auto layer=GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::update(float dt){
	Size winSize=Director::getInstance()->getVisibleSize();
	adjustmentBg-=4;
	if (adjustmentBg<=0) {
		adjustmentBg=winSize.width;
	}
	landSprite1->setPosition(Point(adjustmentBg-winSize.width,landSprite1->getPosition().y));
	landSprite2->setPosition(Point(adjustmentBg,landSprite2->getPosition().y));
}
void	GameScene::startGame(){
	Size winSize=Director::getInstance()->getVisibleSize();
	this->Score=0;
	const char* soreString = String::createWithFormat("%d", Score)->getCString();
	this->lableScore=LabelAtlas::create(soreString, "score.png", 100, 128, 48);
	this->lableScore->setAnchorPoint(Point(0.5, 0.5));
	this->lableScore->setPosition(Point(320, winSize.height*6/7));
	this->addChild(lableScore,2);
	this->mimiSprite->startGame();
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();
	//如果不加入此句消息依旧会向下传递
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [=](Touch* touch,Event* event)
	{
		this->mimiSprite->up();
		return true;
	};
	dispatcher->addEventListenerWithSceneGraphPriority(myListener,this);
	this->schedule(schedule_selector(GameScene::createPipe),1.5);
	this->schedule(schedule_selector(GameScene::collisionDetection),1/60);
 
}
void GameScene::endGame(){
	this->lableScore->removeFromParentAndCleanup(true);
	this->mimiSprite->stopAllActions();
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeAllEventListeners();
	this->mimiSprite->endGame();
	this->unscheduleAllSelectors();
	auto rotate=RotateTo::create(0.15+(this->mimiSprite->getPositionY()-200)/80*0.1,120);
	auto move=MoveTo::create(0.3+(this->mimiSprite->getPositionY()-200)/80*0.1,Point(this->mimiSprite->getPositionX(),102+35));
	//auto move=MoveTo::create(2,Point(0,0));
	auto easeSineIn=EaseSineIn::create(move);
	auto spawn=Spawn::create(easeSineIn,rotate,nullptr);
	auto actCallBack=CallFuncN::create([&](Node *sender){
		int strScore=UserDefault::getInstance()->getIntegerForKey("score");
		if (strScore<this->Score)
		{
			UserDefault::getInstance()->setIntegerForKey("score",this->Score);
			strScore=this->Score;
		}
		Size winSize=Director::getInstance()->getVisibleSize();
		auto highScore=Sprite::createWithSpriteFrameName("highScore.png");
		highScore->setPosition(Point(winSize.width/2,winSize.height*2/3));
		auto scoreLable=LabelAtlas::create(String::createWithFormat("%d",this->Score)->getCString(),"score.png", 100, 128, 48);
		scoreLable->setAnchorPoint(Point(0.5, 0.5));
		scoreLable->setPosition(Point(350,250));
		scoreLable->setScale(0.7f);
		highScore->addChild(scoreLable);
		auto highScoreLable=LabelAtlas::create(String::createWithFormat("%d",strScore)->getCString(),"score.png", 100, 128, 48);
		highScoreLable->setAnchorPoint(Point(0.5, 0.5));
		highScoreLable->setPosition(350,110);
		highScoreLable->setScale(0.7f);
		highScore->addChild(highScoreLable);
		highScore->setScale(0);
		auto scaleOut=ScaleTo::create(0.3f, 1.2f);
		auto scaleIn=ScaleTo::create(0.3f, 1.f);
		auto sequence=Sequence::create(scaleOut,scaleIn, nullptr);
		highScore->runAction(sequence);
		this->addChild(highScore,2);
		auto startButton=MenuItemImage::create("startButton.png", "startButton.png",CC_CALLBACK_1(GameScene::reStartGame, this));
		auto menu=Menu::create(startButton, NULL);
		menu->setPosition(winSize.width/2, 300);
		this->addChild(menu);
	});
	auto sequence=Sequence::create(spawn,actCallBack,nullptr);
	this->mimiSprite->runAction(sequence);
	for(auto& sprite:allPipeSprite){
		sprite->endGame();
	}
}
void GameScene::reStartGame(Ref *pRef){
	TransitionScene *trans=TransitionFade::create(1, StartScene::createScene());
	Director::getInstance()->replaceScene(trans);
}

void GameScene::createPipe(float dt){
	
	//CGFloat y=arc4random() % 200+160;
	Size winSize=Director::getInstance()->getVisibleSize();
	float y=CCRANDOM_0_1()*380+360;
	//PipeSprite *top=[PipeSprite spriteWithTpye:TopPipe];
	PipeSprite *top=PipeSprite::create(TopPipe);
	top->setPosition(Point(winSize.width+top->getBoundingBox().size.width,y+160));
	top->startGame();
	this->allPipeSprite.pushBack(top);
	batchNode->addChild(top);
	PipeSprite *buttom=PipeSprite::create(ButtomPipe);
	buttom->setPosition(Point(winSize.width+top->getBoundingBox().size.width,y-160));
	buttom->startGame();
	this->allPipeSprite.pushBack(buttom);
	batchNode->addChild(buttom);
}
void  GameScene::collisionDetection(float dt){
	if (this->mimiSprite->getPositionY()<147)
	{
		SimpleAudioEngine::getInstance()->playEffect("sounds/dead.wav",false,1);
		this->endGame();
		return;
	}
	for(auto& sprite:allPipeSprite){
		if (sprite->getPositionX()<200&&sprite->getTpye()==TopPipe&&!sprite->isScore) {
			this->Score++;
			this->lableScore->setString(String::createWithFormat("%d",this->Score)->getCString());
			sprite->isScore=true;
			auto scaleOut=ScaleBy::create(0.1f, 2.0f);
			auto scaleIn=ScaleBy::create(0.1f, 0.5f);
			auto sequence=Sequence::create(scaleOut,scaleIn, nullptr);
			this->lableScore->runAction(sequence);
			SimpleAudioEngine::getInstance()->playEffect("score.wav",false,1);
		}
		//降低难度
		Rect rect=this->mimiSprite->getBoundingBox();
		rect.setRect(rect.origin.x+9,rect.origin.y+9,rect.size.width*0.8,rect.size.height*0.8);
		if (sprite->getBoundingBox().intersectsRect(rect))
		{
			SimpleAudioEngine::getInstance()->playEffect("dead.wav",false,1);
			this->endGame();
			return;
		}
	}
}