#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	this->setColor(Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));

	auto _itemStartGame = MenuItemFont::create("Start game", CC_CALLBACK_1(HelloWorld::GoToGameScene, this));

	auto menu = Menu::create(_itemStartGame, NULL);
	menu->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 + 50);
	this->addChild(menu);

	return true;
}

void HelloWorld::GoToGameScene(cocos2d::Ref* ref)
{
	std::vector<int> _vec;
	auto _gameScene = GameScene::createScene(false, 0, 0, _vec);

	srand(time(NULL));
	auto reScene = TransitionFade::create(2.0f, _gameScene, Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}