#include "BonusGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

const int CNT_SECOND_VISIBLE_SUPER_BONUS = 10;

BonusGraphicComponent::BonusGraphicComponent()
{
	m_actived					= false;
	m_openCasket				= false;
	m_showAnimation				= false;
	m_indexInVector				= 0;
	m_indexInVectorAnimation	= 0;
	//m_stateBonus				= StateBonus::BONUS_REST;

	LoadNameSpritesSuperBonus();

	this->initWithFile("res/Weapons/AK47.png");
	this->setVisible(false);

	Size _visibleSize	= Director::getInstance()->getVisibleSize();
	Size _sizeBonus		= this->getContentSize();

	this->setScale(	_visibleSize.width  / _sizeBonus.width / 10,
					_visibleSize.height / _sizeBonus.height / 10
				  );
	this->setPosition(Point(500, 500));

	this->schedule(schedule_selector(BonusGraphicComponent::ShowBonusAnimation), 0.2);

	auto physicBodyBonus = PhysicsBody::createBox(this->getContentSize());
	physicBodyBonus->setContactTestBitmask(true);
	physicBodyBonus->setCollisionBitmask(BONUS_COLLISION_BITMASK);
	physicBodyBonus->setDynamic(false);
	physicBodyBonus->setName("physics");

	this->setPhysicsBody(physicBodyBonus);
}

void BonusGraphicComponent::SetPropertiesBonus(const std::string& i_nameSprites, const std::string& i_nameWeapon, const int& i_typeWeapon)
{
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(i_nameSprites));
	this->m_typeObject = i_nameWeapon;
	this->getPhysicsBody()->setTag(i_typeWeapon);
}

void BonusGraphicComponent::AddBonus(int typeObject)
{
	int _typeObject = typeObject;

	if (_typeObject == CNT_TYPE_OBJECT_RANDOM)
	{
		_typeObject = rand() % 11 + 1;
	}

	switch (_typeObject)
	{
		case CNT_TYPE_OBJECT_CASKET_COINS:
		{
			SetPropertiesBonus(m_vecNameSpritesOpenCasket[m_indexInVector], CNT_NAME_CASKET_COINS, CNT_TYPE_OBJECT_CASKET_COINS);
			LoadNameOpenCakset(CNT_NAME_CASKET_COINS);
			this->m_openCasket = true;

			break;
		}
		case CNT_TYPE_OBJECT_CASKET_POWER:
		{
			SetPropertiesBonus(m_vecNameSpritesOpenCasket[m_indexInVector], CNT_NAME_CASKET_POWERS, CNT_TYPE_OBJECT_CASKET_POWER);
			LoadNameOpenCakset(CNT_NAME_CASKET_POWERS);
			this->m_openCasket = true;
	
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_AK47:
		{
			SetPropertiesBonus("res/Weapons/AK47.png", CNT_NAME_WEAPON_AK47, CNT_TYPE_OBJECT_WEAPON_AK47);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_GUN:
		{
			SetPropertiesBonus("res/Weapons/Gun.png", CNT_NAME_WEAPON_GUN, CNT_TYPE_OBJECT_WEAPON_GUN);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_MI71:
		{
			SetPropertiesBonus("res/Weapons/MI71.png", CNT_NAME_WEAPON_MI71, CNT_TYPE_OBJECT_WEAPON_MI71);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_MK15:
		{
			SetPropertiesBonus("res/Weapons/MK15.png", CNT_NAME_WEAPON_MK15, CNT_TYPE_OBJECT_WEAPON_MK15);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE:
		{
			SetPropertiesBonus("res/Weapons/Revolver_moni_shade.png", CNT_NAME_WEAPON_REVOLVER_MONI_SHADE, CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2:
		{
			SetPropertiesBonus("res/Weapons/Sten_gun_shade_2.png", CNT_NAME_WEAPON_STEN_GUN_SHADE_2, CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_TS23:
		{
			SetPropertiesBonus("res/Weapons/TS23.png", CNT_NAME_WEAPON_TS23, CNT_TYPE_OBJECT_WEAPON_TS23);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_UMG:
		{
			SetPropertiesBonus("res/Weapons/Umg.png", CNT_NAME_WEAPON_UMG, CNT_TYPE_OBJECT_WEAPON_UMG);

			break;
		}
		case CNT_TYPE_OBJECT_BULLET_NORMAL:
		{
			SetPropertiesBonus("res/Bullets/Bullet_normal.png", CNT_NAME_BULLET_DEFAULT, CNT_TYPE_OBJECT_BULLET_NORMAL);

			break;
		}
		case CNT_TYPE_OBJECT_BULLET_BOMB:
		{
			SetPropertiesBonus("res/Bullets/Bomd.png", CNT_NAME_BOMB, CNT_TYPE_OBJECT_BULLET_BOMB);

			break;
		}
	default:
		break;
	}
}

void BonusGraphicComponent::AddSuperBonus(float dt)
{
	srand(time(NULL));
	int _numberSuperBonus = rand() % m_vecNameSpritesSuperBonus.size() + 0;
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesSuperBonus[_numberSuperBonus]));
	//this->m_actived = true;

	switch (_numberSuperBonus)
	{
		case CNT_TYPE_OBJECT_SUPER_DIAMOND:
		{
			this->m_typeObject = CNT_NAME_DIAMOND;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_SUPER_DIAMOND);

			break;
		}
		case CNT_TYPE_OBJECT_SUPER_GOLD:
		{
			this->m_typeObject = CNT_NAME_GOLD;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_SUPER_GOLD);

			break;
		}
		case CNT_TYPE_OBJECT_SUPER_ONYX:
		{
			this->m_typeObject = CNT_NAME_ONYX;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_SUPER_ONYX);

			break;
		}
		case CNT_TYPE_OBJECT_SUPER_RUBY:
		{
			this->m_typeObject = CNT_NAME_RUBY;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_SUPER_RUBY);

			break;
		}
	}

	m_BeginSecond = GetTime();
}

void BonusGraphicComponent::LoadNameSpritesSuperBonus()
{
	m_vecNameSpritesSuperBonus.push_back("res/Bonus/Diamond.png");
	m_vecNameSpritesSuperBonus.push_back("res/Bonus/Gold.png");
	m_vecNameSpritesSuperBonus.push_back("res/Bonus/Onyx.png");
	m_vecNameSpritesSuperBonus.push_back("res/Bonus/Ruby.png");
}

void BonusGraphicComponent::LoadNameOpenCakset(const std::string& typeCasket)
{
	if (typeCasket == CNT_NAME_CASKET_COINS)
	{
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/1.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/2.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/3.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/4.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/5.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/6.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Coins/Coin_1.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Coins/Coin_2.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Coins/Coin_3.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Coins/Coin_4.png");
	}
	else
	{
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/1.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/2.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/3.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/4.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/5.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Casket/6.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Power/life_power_up_1.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Power/life_power_up_2.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Power/life_power_up_3.png");
		m_vecNameSpritesOpenCasket.push_back("res/Bonus/Power/life_power_up_4.png");
	}
}

void BonusGraphicComponent::ShowBonusAnimation(float dt)
{
	if (!m_showAnimation)
	{
		return;
	}

	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesOpenCasket[m_indexInVectorAnimation]));

	if (++m_indexInVectorAnimation == m_vecNameSpritesOpenCasket.size())
	{
		this->m_actived = false;
		m_indexInVectorAnimation = 0;
		this->setPosition(Point(-10, -10));
		this->setVisible(false);
		m_showAnimation = false;
		return;
	}
}

std::chrono::time_point<std::chrono::system_clock> BonusGraphicComponent::GetTime()
{
	std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now();

	return _time;
}

bool BonusGraphicComponent::StopShowSuperBonus()
{
	if ((int)std::chrono::duration<double>(GetTime() - m_BeginSecond).count() == CNT_SECOND_VISIBLE_SUPER_BONUS)
	{
		this->setPosition(Point(-50, -50));
		this->setVisible(false);
		this->m_actived = false;

		return true;
	}
	else
	{
		return false;
	}
}

/*virtual*/ void BonusGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateBonus)
	{
		case Monster::StateBonus::SUPER_BONUS:
		{
			if (StopShowSuperBonus())
			{
				hero.m_stateBonus = Monster::StateBonus::BONUS_REST;
			}
			break;
		}
		case Monster::StateBonus::BONUS_DEATH:
		{
			this->removeFromParentAndCleanup(true);

			break;
		}
	default:
		break;
	}

	return;
}

/*virtual*/ std::string BonusGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

void BonusGraphicComponent::HideObject()
{
	this->setVisible(false);
	this->setPosition(-500, -500);
	this->m_actived = false;
}

/*virtual*/ void BonusGraphicComponent::StartShowAnimation()
{
	this->m_showAnimation = true;
}

BonusGraphicComponent::~BonusGraphicComponent()
{

}

// ***Bonus element*** //
/*
	 casket:
		+ coins;
		+- clothes;
	+ all type weapon;
	- up/down speed;
	+ all type bullet;
*/