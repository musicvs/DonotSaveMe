#include "AppDelegate.h"
#include "scene\TollgateScene.h"

USING_NS_CC;

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
        glview = GLView::create("Don't Save Me!");
        director->setOpenGLView(glview);
    }

    /* ����Win32��Ļ��СΪ480X800, */
    glview->setFrameSize(480, 800);

    /* �򵥵���Ļ���䣬���������죬�����кڱ� */
    glview->setDesignResolutionSize(480, 800, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    /* ��ʼ����Ϊ�ؿ����� */
    auto scene = TollgateScene::scene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}