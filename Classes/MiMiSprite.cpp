#include "MiMiSprite.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
MiMiSprite * MiMiSprite::create(){
	 MiMiSprite *sprite = new MiMiSprite();
	 if (sprite&& sprite->initWithFile("mimi.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
bool MiMiSprite::initWithFile(const std::string& filename){
	if (Sprite::initWithFile(filename))
	{
		this->isStartGame=false;
		return true;
	}
	return false;
}
void MiMiSprite::startGame(){
	g=0;
	a=0;
	isUping=false;
	this->isStartGame=true;
	this->scheduleUpdate();
}
void MiMiSprite::endGame(){
	isStartGame=false;
	this->unscheduleUpdate();
	/*
		CCActionRotateTo *actRotate=[CCActionRotateTo actionWithDuration:0.3 angle:150];
	CCActionMoveTo *moveTo=[CCActionMoveTo actionWithDuration:0.2+(jujuSprite.position.y-100)/40*0.1 position:ccp(100, 70)];
	CCActionEaseSineIn *ae=[CCActionEaseSineIn actionWithAction:moveTo];
	 */
//    auto rotate=RotateTo::create(0.15+(this->getPositionY()-200)/80*0.1,120);
//    auto move=MoveTo::create(0.2+(this->getPositionY()-200)/80*0.1,Point(this->getPositionX(),102+1135));
//    auto easeSineIn=EaseSineIn::create(move);
//    auto spawn=Spawn::create(rotate,easeSineIn,nullptr);
//    auto actCallBack=CallFuncN::create(CC_CALLBACK_1(MiMiSprite::upCallBack, this));
//    auto sequence=Sequence::create(spawn,actCallBack,nullptr);
//    this->runAction(sequence);

}
void MiMiSprite::update(float dt){
	if (!this->isUping&&this->getPositionY()>102+36)
	{
		g+=0.5;
		this->setPositionY(this->getPositionY()-g);
		if (this->getRotation()<180)
		{
			this->setRotation(this->getRotation()+1.0f);
		}
	}
}
void MiMiSprite::up(){
	Size winSize=Director::getInstance()->getVisibleSize();
	if (isStartGame&&this->getPositionY()<winSize.height+200)
	{
		isUping=true;
		auto actRotate=RotateTo::create(0.15,0);
		auto actMoveTo=MoveTo::create(0.3,Point(this->getPositionX(),this->getPositionY()+150));
		auto actEaseSineOut=EaseSineInOut::create(actMoveTo);
		auto actSpawn=Spawn::create(actRotate,actEaseSineOut,nullptr);
		auto actCallBack=CallFuncN::create([&](Node *sender){
			isUping=false;
			g=0;

		});
		auto sequence=Sequence::create(actSpawn,actCallBack,nullptr);
		this->runAction(sequence);
		SimpleAudioEngine::getInstance()->playEffect("jump.wav",false,1);
	}
}
void MiMiSprite::upCallBack(Node *psender){
}
