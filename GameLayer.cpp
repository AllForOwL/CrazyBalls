#include "GameLayer.h"
#include "Monster.h"

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