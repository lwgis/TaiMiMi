#include "cocos2d.h"
USING_NS_CC;
typedef  enum {
	TopPipe=0,
	ButtomPipe=1
}pipeType;
class PipeSprite:public Sprite{
private:
	pipeType type;
public:
	bool isScore;
	static PipeSprite *create(pipeType type);
	virtual bool initWithSpriteFrameName(const std::string& filename);
	virtual void update(float dt);
	void startGame();
	void endGame();
	bool getIsScore();
	pipeType getTpye();
	void setTpye(pipeType type);

};

