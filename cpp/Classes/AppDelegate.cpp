#include "AppDelegate.h"
#include "Constants.h"

// Include Quat's constants

USING_NS_CC;

// Half of iPhone 6's size, just keeps the aspect ratio nice for desktop
// testing 
static cocos2d::Size designResolutionSize = cocos2d::Size(Q_WINDOW_WIDTH, 
                                                          Q_WINDOW_HEIGHT);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
// If we're native and on a desktop platform, just use an arbitrary size
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(Q_EXE_NAME, Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
// Otherwise take the size from the openGL context
#else
        glview = GLViewImpl::create(Q_EXE_NAME);
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(Q_DISPLAY_STATS);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / Q_MAX_FPS);

    // Set the design resolution
    Size frameSize = glview->getFrameSize();

    // We just take the frame's default size since the game handles resolution 
    // independence
    glview->setDesignResolutionSize(frameSize.width, frameSize.height, ResolutionPolicy::SHOW_ALL);

    register_all_packages();
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // create a scene. it's an autorelease object
    this->scene = QUAT::GameScene::create();
    scene->addChild(this->scene);

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    this->scene->enteredBackground();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    this->scene->enteredForeground();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
