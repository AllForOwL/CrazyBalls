#include "BonusGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

BonusGraphicComponent::BonusGraphicComponent()
{
	m_actived					= false;
	m_openCasket				= false;
	m_showAnimation				= false;
	m_indexInVector				= 0;
	m_indexInVectorAnimation	= 0;
	
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
			LoadNameOpenCakset(CNT_NAME_CASKET_COINS);
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesOpenCasket[m_indexInVector]));
			this->m_typeObject = CNT_NAME_CASKET_COINS;
			this->m_openCasket = true;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_CASKET_COINS);

			break;
		}
		case CNT_TYPE_OBJECT_CASKET_POWER:
		{
			LoadNameOpenCakset(CNT_NAME_CASKET_POWERS);
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecNameSpritesOpenCasket[m_indexInVector]));
			this->m_typeObject = CNT_NAME_CASKET_POWERS;
			this->m_openCasket = true;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_CASKET_POWER);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_AK47:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/AK47.png"));
			this->m_typeObject = CNT_NAME_WEAPON_AK47;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_AK47);

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_GUN:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/Gun.png"));
			this->m_typeObject = CNT_NAME_WEAPON_GUN;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_GUN);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_MI71:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/MI71.png"));
			this->m_typeObject = CNT_NAME_WEAPON_MI71;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_MI71);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_MK15:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/MK15.png"));
			this->m_typeObject = CNT_NAME_WEAPON_MK15;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_MK15);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/Revolver_moni_shade.png"));
			this->m_typeObject = CNT_NAME_WEAPON_REVOLVER_MONI_SHADE;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/Sten_gun_shade_2.png"));
			this->m_typeObject = CNT_NAME_WEAPON_STEN_GUN_SHADE_2;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_TS23:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Weapons/TS23.png"));
			this->m_typeObject = CNT_NAME_WEAPON_TS23;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_TS23);

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_UMG:
		{
			this->initWithFile("res/Weapons/Umg.png");
			this->m_typeObject = CNT_NAME_WEAPON_UMG;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_WEAPON_UMG);

			break;

		}
		case CNT_TYPE_OBJECT_BULLET_NORMAL:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Bullets/Bullet_normal.png"));
			this->m_typeObject = CNT_NAME_BULLET_DEFAULT;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_BULLET_NORMAL);

			break;

		}
		case CNT_TYPE_OBJECT_BULLET_BOMB:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage("res/Bullets/Bomd.png"));
			this->m_typeObject = CNT_NAME_BOMB;
			this->getPhysicsBody()->setTag(CNT_TYPE_OBJECT_BULLET_BOMB);

			break;

		}
	default:
		break;
	}
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

/*virtual*/ void BonusGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateBonus)
	{
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

/*virtual*/ int BonusGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ int BonusGraphicComponent::GetHealth() const
{
	return 1;
}

/*virtual*/ std::string BonusGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ bool BonusGraphicComponent::Dead(int wounded)
{
	return true;
}

/*virtual*/ void BonusGraphicComponent::ChangeCoins(int coins)
{

}

/*virtual*/ bool BonusGraphicComponent::Winner() const
{
	return true;
}

/*virtual*/ int BonusGraphicComponent::GetValue() const
{
	return 2;
}

/*virtual*/ void BonusGraphicComponent::SetSpeedBullet(int speed)
{

}

/*virtual*/ int BonusGraphicComponent::GetSpeedBullet() const
{
	return 2;
}

/*virtual*/ void BonusGraphicComponent::DescreaseQuentityBullet()
{

}

/*virtual*/ int BonusGraphicComponent::GetQuentityBullet() const
{
	return 1;
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