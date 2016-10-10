#include "PauseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene *PauseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = PauseScene::create();

	scene->addChild(layer);

	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();

	this->setColor(Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));

	auto _itemGoToMainMenu	= MenuItemFont::create("Main menu",		CC_CALLBACK_1(PauseScene::GoToMainMenu, this));
	auto _itemBackGame		= MenuItemFont::create("Back game",		CC_CALLBACK_1(PauseScene::GoToGame, this));

	_itemGoToMainMenu->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 + 50);
	_itemBackGame->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 - 50);

	auto _menu = Menu::create(_itemGoToMainMenu, _itemBackGame, NULL);
	_menu->setPosition(Point::ZERO);

	this->addChild(_menu);

	return true;
}

void PauseScene::GoToMainMenu(cocos2d::Ref* ref)
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, MainMenuScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}

void PauseScene::GoToGame(cocos2d::Ref* ref)
{
	srand(time(NULL));
	//auto reScene = TransitionFade::create(1.0f, GameScene::createScene(false), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->popScene();
}