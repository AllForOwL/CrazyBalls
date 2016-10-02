#include "GameLayer.h"
#include "Monster.h"
#include "PauseScene.h"

USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	m_lblAttackHero = Label::create();
	m_lblHealthHero = Label::create();
	m_lblCoinsHero  = Label::create();

	cocos2d::Label* _lblPause = Label::create("Pause", "", 10);

	auto _itemMenuPause = MenuItemLabel::create(_lblPause, CC_CALLBACK_1(GameLayer::GoToPause, this));
	_itemMenuPause->setPosition(_visibleSize.width - _itemMenuPause->getContentSize().width,
		_visibleSize.height - _itemMenuPause->getContentSize().height);

	auto menu = Menu::create(_itemMenuPause, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	m_lblAttackHero->setPosition(50, 300);
	m_lblHealthHero->setPosition(100, 300);
	m_lblCoinsHero->setPosition(150, 300);

	this->addChild(m_lblAttackHero);
	this->addChild(m_lblHealthHero);
	this->addChild(m_lblCoinsHero);

	return true;
}

void GameLayer::Update(Monster& hero)
{
	char _health[10];
	char _attack[10];
	char _coins[10];

	itoa(hero.m_graphicComponentHero->GetAttack(), _attack, 10);
	itoa(hero.m_graphicComponentHero->GetHealth(), _health, 10);
	itoa(hero.m_graphicComponentHero->GetValue(), _coins, 10);

	m_lblAttackHero->setString(_attack);
	m_lblHealthHero->setString(_health);
	m_lblCoinsHero->setString(_coins);
}

void GameLayer::GoToPause(cocos2d::Ref* ref)
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, PauseScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->pushScene(reScene);
	//Director::getInstance()->replaceScene(reScene);
}