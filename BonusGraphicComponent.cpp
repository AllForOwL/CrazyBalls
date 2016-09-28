#include "BonusGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

BonusGraphicComponent::BonusGraphicComponent()
{
	m_actived		= false;
	m_openCasket	= false;
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
			LoadNameOpenCakset();
			this->initWithFile(m_vecNameSpritesOpenCasket[0]);
			this->m_typeObject = CNT_NAME_CASKET_COINS;
			this->m_openCasket = true;

			break;
		}
		case CNT_TYPE_OBJECT_CASKET_CLOTHES:
		{
			LoadNameOpenCakset();
			this->initWithFile(m_vecNameSpritesOpenCasket[0]);
			this->m_typeObject = CNT_NAME_CASKET_CLOTHES;
			this->m_openCasket = true;

			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_AK47:
		{
			this->initWithFile("res/Weapons/AK47.png");
			this->m_typeObject = CNT_NAME_WEAPON_AK47;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_GUN:
		{
			this->initWithFile("res/Weapons/Gun.png");
			this->m_typeObject = CNT_NAME_WEAPON_GUN;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_MI71:
		{
			this->initWithFile("res/Weapons/MI71.png");
			this->m_typeObject = CNT_NAME_WEAPON_MI71;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_MK15:
		{
			this->initWithFile("res/Weapons/MK15.png");
			this->m_typeObject = CNT_NAME_WEAPON_MK15;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE:
		{
			this->initWithFile("res/Weapons/Revolver_moni_shade.png");
			this->m_typeObject = CNT_NAME_WEAPON_REVOLVER_MONI_SHADE;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2:
		{
			this->initWithFile("res/Weapons/Sten_gun_shade_2.png");
			this->m_typeObject = CNT_NAME_WEAPON_STEN_GUN_SHADE_2;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_TS23:
		{
			this->initWithFile("res/Weapons/TS23.png");
			this->m_typeObject = CNT_NAME_WEAPON_TS23;

			break;

		}
		case CNT_TYPE_OBJECT_WEAPON_UMG:
		{
			this->initWithFile("res/Weapons/Umg.png");
			this->m_typeObject = CNT_NAME_WEAPON_UMG;

			break;

		}
		case CNT_TYPE_OBJECT_BULLET_NORMAL:
		{
			this->initWithFile("res/Bullets/Bullet_normal.png");
			this->m_typeObject = CNT_NAME_BULLET_DEFAULT;

			break;

		}
		case CNT_TYPE_OBJECT_BULLET_BOMB:
		{
			this->initWithFile("res/Bullets/Bomd.png");
			this->m_typeObject = CNT_NAME_WEAPON_AK47;

			break;

		}
	default:
		break;
	}

}

void BonusGraphicComponent::LoadNameOpenCakset()
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

/*virtual*/ void BonusGraphicComponent::Update(Monster& hero, GameScene& scene)
{
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

BonusGraphicComponent::~BonusGraphicComponent()
{

}


// ***Bonus element*** //
/*
	- casket:
		- coins;
		- clothes;
	- all type weapon;
	- up/down speed;
	- all type bullet;
*/