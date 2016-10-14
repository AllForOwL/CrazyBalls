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

const int CNT_INDEX_COIN = 0;
const int CNT_INDEX_POWER = 1;
const int CNT_INDEX_WEAPON = 2;

USING_NS_CC;

std::string to_string(int i)
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
	
	m_veclblProperties.push_back(Label::create());
	m_veclblProperties.push_back(Label::create());
	m_veclblProperties.push_back(Label::create());

	m_vecsprProperties.push_back(Sprite::create("res/Bonus/Coins/Coin_1.png"));
	m_vecsprProperties.push_back(Sprite::create("res/Bonus/Power/life_power_up_1.png"));
	m_vecsprProperties.push_back(Sprite::create("res/Weapons/AK47.png"));

	for (int i = 0; i < m_vecsprProperties.size(); i++)
	{
		Size _sizeSprite = m_vecsprProperties[i]->getContentSize();
		m_vecsprProperties[i]->setScale(m_visibleSize.width /_sizeSprite.width / CNT_SCALE,
			m_visibleSize.height / _sizeSprite.height / CNT_SCALE);
	}

	Point _position = Point::ZERO;
	Size _sizeSpriteAfterScale = m_vecsprProperties[0]->getBoundingBox().size;
	_position.y = m_visibleSize.height - (_sizeSpriteAfterScale.height * 2);

	for (int i = 0; i < 6; i++)
	{
		_position.x += _sizeSpriteAfterScale.width * 2;
		m_vecPointProperties.push_back(_position);
	}

	m_vecsprProperties[CNT_INDEX_COIN]->setPosition(m_vecPointProperties[0]);
	m_vecsprProperties[CNT_INDEX_POWER]->setPosition(m_vecPointProperties[2]);
	m_vecsprProperties[CNT_INDEX_WEAPON]->setPosition(m_vecPointProperties[4]);

	m_veclblProperties[CNT_INDEX_COIN]->setPosition(m_vecPointProperties[1]);
	m_veclblProperties[CNT_INDEX_POWER]->setPosition(m_vecPointProperties[3]);
	m_veclblProperties[CNT_INDEX_WEAPON]->setPosition(m_vecPointProperties[5]);

	for (int i = 0; i < 3; i++)
	{
		this->addChild(m_vecsprProperties[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		this->addChild(m_veclblProperties[i]);
	}

	return true;
}

void GameLayer::Update(Monster& hero)
{
	std::string _strCoin	= std::to_string(hero.m_graphicComponentHero->GetValue());
	std::string _strHealth	= std::to_string(hero.m_graphicComponentHero->GetHealth());

	m_veclblProperties[CNT_INDEX_COIN]->setString	(_strCoin);
	m_veclblProperties[CNT_INDEX_POWER]->setString	(_strHealth);

	switch (hero.m_stateBonus)
	{
		case Monster::StateBonus::BONUS_TAKE_COIN:
		{
			_strCoin = std::to_string(hero.m_graphicComponentHero->GetValue());
			m_veclblProperties[CNT_INDEX_COIN]->setString(_strCoin);

			hero.m_stateBonus = Monster::StateBonus::BONUS_WEAPON;
				
			break;
		}

		case Monster::StateBonus::BONUS_TAKE_POWER:
		{
			_strHealth = std::to_string(hero.m_graphicComponentHero->GetHealth());
			m_veclblProperties[CNT_INDEX_POWER]->setString(_strHealth);

			hero.m_stateBonus = Monster::StateBonus::BONUS_WEAPON;

			break;
		}
		case Monster::StateBonus::BONUS_WEAPON:
		{
			int _indexActiveWeapon = hero.GetIndexActiveWeapon();

			int _quentityBullet = hero.m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->GetQuentityBullet();
			std::string	_nameWeapon	= hero.m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->GetFileName();

			m_veclblProperties[CNT_INDEX_WEAPON]->setString(std::to_string(_quentityBullet));
			m_vecsprProperties[CNT_INDEX_WEAPON]->create(_nameWeapon);

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

/******Need set position on this layer********/