#include "GameOverScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene *GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();

	this->setColor(Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));

	auto _itemGoToMainMenu	= MenuItemFont::create("Main menu", CC_CALLBACK_1(GameOverScene::GoToMainMenu, this));
	auto _itemExit			= MenuItemFont::create("EXIT",		CC_CALLBACK_1(GameOverScene::Exit, this));

	_itemGoToMainMenu->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 + 50);
	_itemExit->setPosition(_visibleSize.width / 2, _visibleSize.height / 2 - 50);

	auto _menu = Menu::create(_itemGoToMainMenu, _itemExit, NULL);
	_menu->setPosition(Point::ZERO);

	this->addChild(_menu);

	return true;
}

void GameOverScene::GoToMainMenu(cocos2d::Ref* ref)
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, MainMenuScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}

void GameOverScene::Exit(cocos2d::Ref* ref)
{

}