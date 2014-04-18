#include "PipeSprite.h"

bool PipeSprite::initWithFile(const std::string& filename){
	if (Sprite::initWithFile(filename))
	{
		//this->isStartGame=false;
        this->isScore=false;
		return true;
	}
	return false;
}

 PipeSprite* PipeSprite::create(pipeType type){
	PipeSprite *pSprite=new PipeSprite();
	if (type==TopPipe)
	{
		pSprite->initWithFile("topPipe.png");
		pSprite->setAnchorPoint(Point(1,0));
	}
	else
	{
		pSprite->initWithFile("buttomPipe.png");
		pSprite->setAnchorPoint(Point(1,1));
	}
	pSprite->autorelease();
     pSprite->setTpye(type);
	//CC_SAFE_DELETE(pSprite);
	return pSprite;
 }

 void PipeSprite::update(float dt){
	 if (this->getPositionX()<0) {
		 this->removeFromParentAndCleanup(true);
        return;
    }
	 this->setPosition(Point(this->getPositionX()-4, this->getPositionY()));

 }
  void PipeSprite::startGame(){
	this->scheduleUpdate();
 } void PipeSprite::endGame(){
	 this->unscheduleUpdate();
 }
pipeType PipeSprite::getTpye(){
    return this->type;
}
void PipeSprite::setTpye(pipeType type){
    this->type=type;
}




