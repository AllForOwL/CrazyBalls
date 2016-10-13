#include <stdio.h>
#include <stdlib.h>

#include "GameLayer.h"
#include "Monster.h"
#include "PauseScene.h"
#include "constants.h"

const int CNT_SCALE = 25;

const std::string CNT_ANIMATION_COIN	= "Animation coin";
const std::string CNT_ANIMATION_POWER	= "Animation power";

USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();

	LoadSpritesName();
	m_animationPower	= Sprite::create("res/Bonus/Power/life_power_up_1.png");
	Size _sizeSprite	= m_animationPower->getContentSize();
	m_animationPower->setScale(_visibleSize.width / _sizeSprite.width / CNT_SCALE,
		_visibleSize.height / _sizeSprite.height / CNT_SCALE);

	m_animationCoin		= Sprite::create("res/Bonus/Coins/Coin_1.png");
	_sizeSprite	= m_animationCoin->getContentSize();
	m_animationCoin->setScale(_visibleSize.width / _sizeSprite.width / CNT_SCALE,
		_visibleSize.height / _sizeSprite.height / CNT_SCALE);


	this->addChild(m_animationPower);
	this->addChild(m_animationCoin);

	m_indexInVectorAnimation = 0;

	m_vecNameSpritesWeapon.push_back("res/Weapons/AK47.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/Gun.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/MI71.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/MK15.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/Revolver_moni_shade.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/Sten_gun_shade_2.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/TS23.png");
	m_vecNameSpritesWeapon.push_back("res/Weapons/Umg.png");


	for (int i = 0; i < m_vecNameSpritesWeapon.size(); i++)
	{
		Sprite* _tempWeapon = Sprite::create(m_vecNameSpritesWeapon[i]);
		m_vecSpritesWeapon.push_back(_tempWeapon);
		m_vecSpritesWeapon[i]->setTag(i);
	}

	for (int i = 0; i < m_vecSpritesWeapon.size(); i++)
	{
		_sizeSprite = m_vecSpritesWeapon[i]->getContentSize();
		m_vecSpritesWeapon[i]->setScale(_visibleSize.width / _sizeSprite.width / CNT_SCALE,
			_visibleSize.height / _sizeSprite.height / CNT_SCALE);

		Label* _labelQuentityBullet = Label::create();
		m_vecLevelQuentityBullet.push_back(_labelQuentityBullet);
	}

	m_vecNameSpritesBonus.push_back("res/Bonus/Coins/Coin_1.png");
	m_vecNameSpritesBonus.push_back("res/Bonus/Power/life_power_up_1.png");
	m_vecNameSpritesBonus.push_back("res/Bonus/Onyx.png");

	for (int i = 0; i < m_vecNameSpritesBonus.size(); i++)
	{
		Sprite* _tempBonus = Sprite::create(m_vecNameSpritesBonus[i]);
		m_vecSpritesBonus.push_back(_tempBonus);
	}

	for (int i = 0; i < m_vecSpritesBonus.size(); i++)
	{
		_sizeSprite = m_vecSpritesBonus[i]->getContentSize();
		m_vecSpritesBonus[i]->setScale(_visibleSize.width / _sizeSprite.width / CNT_SCALE,
			_visibleSize.height / _sizeSprite.height / CNT_SCALE);
	}

	m_lblAttackHero = Label::create();
	m_lblHealthHero = Label::create();
	m_lblCoinsHero  = Label::create();

	cocos2d::Label* _lblPause = Label::create("Pause", "", 12);

	auto _itemMenuPause = MenuItemLabel::create(_lblPause, CC_CALLBACK_1(GameLayer::GoToPause, this));
	_itemMenuPause->setPosition(_visibleSize.width - _itemMenuPause->getContentSize().width,
		_visibleSize.height - _itemMenuPause->getContentSize().height);

	auto menu = Menu::create(_itemMenuPause, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	m_vecSpritesBonus[0]->setPosition(30, 300);
	m_lblAttackHero->setPosition(60, 300);

	m_vecSpritesBonus[1]->setPosition(90, 300);
	m_lblHealthHero->setPosition(120, 300);

	m_vecSpritesBonus[2]->setPosition(150, 300);
	m_lblCoinsHero->setPosition(180, 300);

	m_positionX = 210;

	this->addChild(m_lblAttackHero);
	this->addChild(m_lblHealthHero);
	this->addChild(m_lblCoinsHero);

	for (int i = 0; i < m_vecNameSpritesWeapon.size(); i++)
	{
		this->addChild(m_vecSpritesWeapon[i]);
		this->addChild(m_vecLevelQuentityBullet[i]);
	}
	
	for (int i = 0; i < m_vecSpritesBonus.size(); i++)
	{
		this->addChild(m_vecSpritesBonus[i]);
	}

	this->schedule(schedule_selector(GameLayer::ShowAnimation), 0.5);

	return true;
}

void GameLayer::ShowAnimation(float dt)
{
	if (m_typeAnimation == CNT_ANIMATION_COIN)
	{
		if (m_indexInVectorAnimation == 0)
		{
			m_vecSpritesBonus[0]->setVisible(false);
			m_animationCoin->setPosition(30, 300);
			m_animationCoin->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesAnimationCoin[m_indexInVectorAnimation]));
		}
		else
		{
			m_animationCoin->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesAnimationCoin[m_indexInVectorAnimation]));
		}

		if (++m_indexInVectorAnimation == m_vecNameSpritesAnimationCoin.size())
		{
			m_vecSpritesBonus[0]->setVisible(true);
			m_typeAnimation = "";
			m_indexInVectorAnimation = 0;
			m_animationPower->setPosition(-100, -100);
		}
	}
	else if (m_typeAnimation == CNT_ANIMATION_POWER)
	{
		if (m_indexInVectorAnimation == 0)
		{
			m_vecSpritesBonus[1]->setVisible(false);
			m_animationPower->setPosition(90, 300);
			m_animationPower->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesAnimationPower[m_indexInVectorAnimation]));
		}
		else
		{
			m_animationPower->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesAnimationPower[m_indexInVectorAnimation]));
		}

		if (++m_indexInVectorAnimation == m_vecNameSpritesAnimationCoin.size())
		{
			m_vecSpritesBonus[1]->setVisible(true);
			m_typeAnimation = "";
			m_indexInVectorAnimation = 0;
			m_animationPower->setPosition(-100, -100);
		}
	}
}

void GameLayer::ShowQuentityBullet(int tagWeapon, int quentityBullet)
{
		int _tagWeapon		= tagWeapon;
		int _quentityBullet = quentityBullet;

		int _index = _tagWeapon - 3;												
		if (m_vecLevelQuentityBullet[_index]->getTag() == _tagWeapon)
		{
			char _chquentityBullet[10];
			itoa(_quentityBullet, _chquentityBullet, 10);
			m_vecLevelQuentityBullet[_index]->setString(_chquentityBullet);
		}
		else
		{
			m_vecSpritesWeapon[_index]->setPosition(m_positionX, 300);

			m_positionX += 30;
			char _chquentityBullet[10];
			itoa(_quentityBullet, _chquentityBullet, 10);
			m_vecLevelQuentityBullet[_index]->setString(_chquentityBullet);
			m_vecLevelQuentityBullet[_index]->setPosition(m_positionX, 300);
			m_vecLevelQuentityBullet[_index]->setTag(_tagWeapon);

			m_positionX += 30;
		}
}

void GameLayer::LoadSpritesName()
{
	m_vecNameSpritesAnimationPower.push_back("res/Bonus/Power/life_power_up_1.png");
	m_vecNameSpritesAnimationPower.push_back("res/Bonus/Power/life_power_up_2.png");
	m_vecNameSpritesAnimationPower.push_back("res/Bonus/Power/life_power_up_3.png");
	m_vecNameSpritesAnimationPower.push_back("res/Bonus/Power/life_power_up_4.png");
	
	m_vecNameSpritesAnimationCoin.push_back("res/Bonus/Coins/Coin_1.png");
	m_vecNameSpritesAnimationCoin.push_back("res/Bonus/Coins/Coin_2.png");
	m_vecNameSpritesAnimationCoin.push_back("res/Bonus/Coins/Coin_3.png");
	m_vecNameSpritesAnimationCoin.push_back("res/Bonus/Coins/Coin_4.png");
}

void GameLayer::Update(Monster& hero)
{
	char _health[10];
	char _attack[10];
	char _coins[10];

	itoa(hero.m_graphicComponentHero->GetAttack(),	_attack, 10);
	itoa(hero.m_graphicComponentHero->GetHealth(),	_health, 10);
	itoa(hero.m_graphicComponentHero->GetValue(),	_coins,  10);

	m_lblAttackHero->setString	(_attack);
	m_lblHealthHero->setString	(_health);
	m_lblCoinsHero->setString	(_coins);

	switch (hero.m_stateBonus)
	{
		case Monster::StateBonus::BONUS_TAKE_COIN:
		{
			itoa(hero.m_graphicComponentHero->GetAttack(), _coins, 10);
			m_lblAttackHero->setString(_coins);

			m_typeAnimation = CNT_ANIMATION_COIN;
			hero.m_stateBonus = Monster::StateBonus::BONUS_WEAPON;
				
			break;
		}

		case Monster::StateBonus::BONUS_TAKE_POWER:
		{
			itoa(hero.m_graphicComponentHero->GetHealth(), _health, 10);
			m_lblHealthHero->setString(_health);

			m_typeAnimation = CNT_ANIMATION_POWER;
			hero.m_stateBonus = Monster::StateBonus::BONUS_WEAPON;

			break;
		}
		case Monster::StateBonus::BONUS_WEAPON:
		{
			for (int i = 0; i < hero.m_vecGraphicComponentWeapon.size(); i++)
			{
				int _tagWeapon		= hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->getTag();
				int _quentityBullet = hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->GetQuentityBullet();	

				ShowQuentityBullet(_tagWeapon, _quentityBullet);
			}
			break;
		}
		default:
			break;
	}
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