#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

#define DISPLAY_TIME_SPLASH_SCENE	1
#define TRANSITION_TIME				0.5

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);	// обработчик событий(функция обработки, время появления)

	auto background = Sprite::create("imgBcgWelcome.png");
	background->setPosition(Point(visibleSize.width	 / 2,
								  visibleSize.height / 2
								 )
						   );
	this->addChild(background);

    return true;
}

void SplashScene::GoToMainMenuScene(float delay)
{
	auto mainMenuScene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, mainMenuScene));
}
