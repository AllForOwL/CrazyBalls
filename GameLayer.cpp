#include <iostream>
#include <string>
#include <sstream>	
#include "GameLayer.h"
#include "Monster.h"
#include "PauseScene.h"
#include "constants.h"
#include "WeaponGraphicComponent.h"

using namespace std;

const int CNT_SCALE = 25;

const std::string CNT_ANIMATION_COIN	= "Animation coin";
const std::string CNT_ANIMATION_POWER	= "Animation power";

const int CNT_INDEX_COIN	= 0;
const int CNT_INDEX_POWER	= 1;
const int CNT_INDEX_WEAPON	= 2;
const int CNT_INDEX_ARMOR   = 3;

USING_NS_CC;

std::string GameLayer::to_string(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

bool GameLayer::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();
	
	m_menuBarBottom = Sprite::create("res/Menu/BarBottomGood.jpg");
	m_menuBarBottom->setScale(m_visibleSize.width / m_menuBarBottom->getContentSize().width,
		m_visibleSize.height / m_menuBarBottom->getContentSize().height / 6);
	m_menuBarBottom->setPosition(m_visibleSize.width / 2, m_menuBarBottom->getBoundingBox().size.height / 2);
	this->addChild(m_menuBarBottom);

	m_veclblProperties.push_back(CCLabelTTF::create("", "res/Fonts/kenvector_future.ttf", 18));
	m_veclblProperties.push_back(CCLabelTTF::create("", "res/Fonts/kenvector_future.ttf", 18));
	m_veclblProperties.push_back(CCLabelTTF::create("", "res/Fonts/kenvector_future.ttf", 18));
	m_veclblProperties.push_back(CCLabelTTF::create("", "res/Fonts/kenvector_future.ttf", 18));

	//_position.y = m_visibleSize.height - (_sizeSpriteAfterScale.height * 2);
	/*for (int i = 0; i < 6; i++)
	{
		_position.x += _sizeSpriteAfterScale.width * 2;
		m_vecPointProperties.push_back(_position);
	}*/

	m_veclblProperties[CNT_INDEX_COIN]->setPosition(m_menuBarBottom->getBoundingBox().size.width / 2 + 47,
		m_menuBarBottom->getBoundingBox().size.height - 40);
	m_veclblProperties[CNT_INDEX_POWER]->setPosition(m_menuBarBottom->getBoundingBox().size.width / 2 + 42,
		m_menuBarBottom->getBoundingBox().size.height - 15);
	m_veclblProperties[CNT_INDEX_WEAPON]->setPosition(m_menuBarBottom->getBoundingBox().size.width / 2 + 150,
		m_menuBarBottom->getBoundingBox().size.height - 40);
	m_veclblProperties[CNT_INDEX_ARMOR]->setPosition(m_menuBarBottom->getBoundingBox().size.width / 2 + 150, 
		m_menuBarBottom->getBoundingBox().size.height - 15);

	for (int i = 0; i < 4; i++)
	{
		m_veclblProperties[i]->setFontFillColor(Color3B(Color3B::GRAY));
		this->addChild(m_veclblProperties[i]);
	}

	return true;
}

void GameLayer::Update(Monster& hero)
{
	std::string _strCoin	= to_string(hero.m_graphicComponentHero->GetValue());
	std::string _strHealth	= to_string(hero.m_graphicComponentHero->GetHealth());

	m_veclblProperties[CNT_INDEX_COIN]->setString	(_strCoin);
	m_veclblProperties[CNT_INDEX_POWER]->setString	(_strHealth);
}

void GameLayer::GoToPause(cocos2d::Ref* ref)
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, PauseScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->pushScene(reScene);
}

/*	04:10:16
Animation:
	+ power;
	+ coin;
	- onyx(by kills enemy); // not need
	- chooise counter in ends level (second from three bonuses):
		1 - power;
		2 - weapon;
		3 - ball for kills enemy(onyx);
	- save on next level chooises counter;
*/

////*** Tasks ****////	Mission complete

/* 
	+ Need set position on this layer
	+ Change weapon when touch on hero
	+ refactoring GameLayer
*/