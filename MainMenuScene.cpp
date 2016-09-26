#include "MainMenuScene.h"

USING_NS_CC;

Scene *MainMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();

	///auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
	//	CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));


	//auto menu = Menu::create(closeItem, NULL);
	//this->addChild(menu, 1);


	return true;
}