#include "AppDelegate.h"
#include "Scene/StartScene.hpp"

// #define USE_AUDIO_ENGINE 1
#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1000, 600);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("DungeonMario", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("DungeonMario");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
    
    preloadMusic();
    preloadStaticPics();
    preloadAnimations();

    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

void AppDelegate::preloadMusic() {
    log("[AppDelegate :] load Music [Start]");
	
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("mp3/BGM/TianAnMen.mp3");
	audio->preloadBackgroundMusic("mp3/BGM/EnterNewStage.mp3");
	audio->preloadBackgroundMusic("mp3/BGM/SMBSM3DL_4.mp3");
	audio->preloadEffect("mp3/BGM/Congratulations.mp3");

	audio->preloadEffect("mp3/Effect/1up.mp3");
	audio->preloadEffect("mp3/Effect/coin.mp3");
	audio->preloadEffect("mp3/Effect/jump.mp3");
	audio->preloadEffect("mp3/Effect/slide.mp3");
	audio->preloadEffect("mp3/Effect/spring.mp3");
	
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.7f);

	log("[AppDelegate :] load Music [Completed]");
}

void AppDelegate::preloadStaticPics() {
    log("[AppDelegate :] load Static Pics [Start]");
	// destPoint, IceRock, Mushroom, StartPoint, Tanhuang
	auto textureStaticPics = Director::getInstance()->getTextureCache()->addImage("ObjectPics/staticpics.png");
	auto destPointFrame = SpriteFrame::createWithTexture(textureStaticPics, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 32, 32)));
	SpriteFrameCache::getInstance()->addSpriteFrame(destPointFrame, "DestinationPoint.png");
	auto iceRockFrame = SpriteFrame::createWithTexture(textureStaticPics, CC_RECT_PIXELS_TO_POINTS(Rect(32, 0, 32, 32)));
	SpriteFrameCache::getInstance()->addSpriteFrame(iceRockFrame, "IceRock.png");
	auto mushroomFrame = SpriteFrame::createWithTexture(textureStaticPics, CC_RECT_PIXELS_TO_POINTS(Rect(64, 0, 32, 32)));
	SpriteFrameCache::getInstance()->addSpriteFrame(mushroomFrame, "Mushroom.png");
	auto startPointFrame = SpriteFrame::createWithTexture(textureStaticPics, CC_RECT_PIXELS_TO_POINTS(Rect(96, 0, 32, 32)));
	SpriteFrameCache::getInstance()->addSpriteFrame(startPointFrame, "StartPoint.png");
	auto tanhuangFrame = SpriteFrame::createWithTexture(textureStaticPics, CC_RECT_PIXELS_TO_POINTS(Rect(128, 0, 32, 32)));
	SpriteFrameCache::getInstance()->addSpriteFrame(tanhuangFrame, "Tanhuang.png");
	log("test create with texture END");
    
    Director::getInstance()->getTextureCache()->addImage("ObjectPics/MarioBig.png");
    
    auto plainRockTexture = Director::getInstance()->getTextureCache()->addImage("ObjectPics/PlainRock.png");
    for (int i = 0; i < 6; i++) {
        std::stringstream ss;
        ss << "PlainRock-" << i << ".png";
        auto frame = SpriteFrame::createWithTexture(plainRockTexture, CC_RECT_PIXELS_TO_POINTS(Rect(0, i * 32, 32, 32)));
        SpriteFrameCache::getInstance()->addSpriteFrame(frame, ss.str());
    }
    
    log("[AppDelegate :] load Static Pics [Completed]");
}

void AppDelegate::preloadAnimations() {
    log("[AppDelegate :] load Animation [Start]");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ObjectAnimations/coin.plist");
    auto coinAnimation = Animation::create();
    for (int i = 0; i < 4; i++) {
        std::stringstream ss;
        ss << "coin-" << i << ".png";
        coinAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
    }
    coinAnimation->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(coinAnimation, "coinAnimation");

	auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("coin-1.png");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ObjectAnimations/key.plist");
    auto keyAnimation = Animation::create();
    for (int i = 0; i < 10; i++) {
        std::stringstream ss;
        ss << "key-" << i << ".png";
        keyAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
    }
    keyAnimation->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(keyAnimation, "keyAnimation");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ObjectAnimations/platform.plist");
    auto platformAnimation = Animation::create();
    for (int i = 0; i < 4; i++) {
        std::stringstream ss;
        ss << "platform-" << i << ".png";
        platformAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
    }
    platformAnimation->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(platformAnimation, "platformAnimation");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ObjectAnimations/spike.plist");
    auto spikeAnimation = Animation::create();
    for (int i = 0; i < 5; i++) {
        std::stringstream ss;
        ss << "spike-" << i << ".bmp";
        spikeAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
    }
    spikeAnimation->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(spikeAnimation, "spikeAnimation");
    
    auto turtleTexture = Director::getInstance()->getTextureCache()->addImage("ObjectAnimations/turtle.png");
    cocos2d::Vector<SpriteFrame*> TurtleIdleLeft, TurtleIdleRight;
    TurtleIdleLeft.reserve(4);
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(turtleTexture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 56 * i, 32, 56)));
        TurtleIdleLeft.pushBack(frame);
    }
    Animation* TurtleIdleLeftAnimation = Animation::createWithSpriteFrames(TurtleIdleLeft, 0.1f);
    AnimationCache::getInstance()->addAnimation(TurtleIdleLeftAnimation, "TurtleIdleLeftAnimation");
    
    TurtleIdleRight.reserve(4);
    for (int i = 0; i < 4; i++) {
        auto frame = SpriteFrame::createWithTexture(turtleTexture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 56 * (i + 4), 32, 56)));
        TurtleIdleRight.pushBack(frame);
    }
    Animation* TurtleIdleRightAnimation = Animation::createWithSpriteFrames(TurtleIdleRight, 0.1f);
    AnimationCache::getInstance()->addAnimation(TurtleIdleRightAnimation, "TurtleIdleRightAnimation");
    
    auto chestnutTexture = Director::getInstance()->getTextureCache()->addImage("ObjectAnimations/chestnut.png");
    cocos2d::Vector<SpriteFrame*> chestnutPatrol;
    chestnutPatrol.reserve(2);
    for (int i = 0; i < 2; i++) {
        auto frame = SpriteFrame::createWithTexture(chestnutTexture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 32 * i, 32, 32)));
        chestnutPatrol.pushBack(frame);
    }
    Animation* chestnutPatrolAnimation = Animation::createWithSpriteFrames(chestnutPatrol, 0.1f);
    AnimationCache::getInstance()->addAnimation(chestnutPatrolAnimation, "chestnutPatrolAnimation");
    
    log("[AppDelegate :] load Animation [Completed]");
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
