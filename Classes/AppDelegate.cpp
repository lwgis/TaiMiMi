#include "AppDelegate.h"
#include "StartScene.h"
USING_NS_CC;
#define iphone4 640,960 
#define iphone5 640,1136
#define iphone3  320,480
#define p720 720,1280

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("~抬小白~");
		glview->setFrameSize(320,568);
		director->setOpenGLView(glview);
	}
	Platform platform = Application::getInstance()->getTargetPlatform();
	if (platform==Platform::OS_ANDROID||platform==Platform::OS_WINDOWS) {
		glview->setDesignResolutionSize(640,1136,ResolutionPolicy::SHOW_ALL);
	}
	
	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = StartScene::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
