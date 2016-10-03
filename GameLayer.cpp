#include "GameLayer.h"
#include "Monster.h"
#include "PauseScene.h"
#include "constants.h"

const int CNT_SCALE = 25;

USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
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

	Size _sizeSprite;
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

	return true;
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

	for (int i = 0; i < hero.m_vecGraphicComponentWeapon.size(); i++)
	{
		int _tagWeapon = hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->getTag();
		int _quentityBullet = hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->GetQuentityBullet();

		switch (_tagWeapon)
		{
			case CNT_TYPE_OBJECT_WEAPON_AK47:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_AK47 - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_AK47)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_AK47);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_GUN:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_GUN - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_GUN)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_GUN);

					m_positionX += 30;
				}
				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_MI71:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_MI71 - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_MI71)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_MI71);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_MK15:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_MK15 - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_MK15)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_MK15);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2 - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_TS23:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_TS23 - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_TS23)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_TS23);

					m_positionX += 30;
				}

				break;
			}
			case CNT_TYPE_OBJECT_WEAPON_UMG:
			{
				int _index = CNT_TYPE_OBJECT_WEAPON_UMG - 3;												
				if (m_vecLevelQuentityBullet[_index]->getTag() == CNT_TYPE_OBJECT_WEAPON_UMG)
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
					m_vecLevelQuentityBullet[_index]->setTag(CNT_TYPE_OBJECT_WEAPON_UMG);

					m_positionX += 30;
				}
				
				this->addChild(m_vecSpritesWeapon[_index]);

				break;
				break;
			}
		default:
			break;
		}

	}
}

void GameLayer::GoToPause(cocos2d::Ref* ref)
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, PauseScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->pushScene(reScene);
}