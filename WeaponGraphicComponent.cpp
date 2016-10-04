#include "WeaponGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

WeaponGraphicComponent::WeaponGraphicComponent(int attack, const std::string& typeObject)
												: m_attack		(attack),
												  m_typeObject	(typeObject)
{
	if (m_typeObject == CNT_NAME_WEAPON_AK47)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_AK47);
		m_strFilename = "res/Weapons/AK47.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 8;
		m_quentityBullet	= 2;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_GUN)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_GUN);
		m_strFilename = "res/Weapons/Gun.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 9;
		m_quentityBullet	= 15;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MI71)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_MI71);
		m_strFilename = "res/Weapons/MI71.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 10;
		m_quentityBullet	= 20;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MK15)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_MK15);
		m_strFilename = "res/Weapons/MK15.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 11;
		m_quentityBullet	= 25;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_REVOLVER_MONI_SHADE)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE);
		m_strFilename = "res/Weapons/Revolver_moni_shade.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 12;
		m_quentityBullet	= 30;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_STEN_GUN_SHADE_2)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2);
		m_strFilename = "res/Weapons/Sten_gun_shade_2.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 13;
		m_quentityBullet	= 35;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_TS23)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_TS23);
		m_strFilename = "res/Weapons/TS23.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 14;
		m_quentityBullet	= 40;
	}
	else if (m_typeObject == CNT_NAME_WEAPON_UMG)
	{
		this->setTag(CNT_TYPE_OBJECT_WEAPON_UMG);
		m_strFilename = "res/Weapons/Umg.png";
		this->initWithFile(m_strFilename);
		m_speedBullet		= 14;
		m_quentityBullet	= 45;
	}

	this->setName(m_typeObject);

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	Size _sizeWeapon  = this->getContentSize();

	this->setScale(_visibleSize.width / _sizeWeapon.width / 8,
		_visibleSize.height / _sizeWeapon.height / 8);
}

WeaponGraphicComponent::WeaponGraphicComponent(WeaponGraphicComponent& weapon)
{
	this->m_attack		= weapon.GetAttack();
	this->m_typeObject	= weapon.GetTypeObject();
	
	if (m_typeObject == CNT_NAME_WEAPON_AK47)
	{
		m_strFilename = "AK7.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_GUN)
	{
		m_strFilename = "Gun.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MI71)
	{
		m_strFilename = "MI71.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MK15)
	{
		m_strFilename = "MK15.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_REVOLVER_MONI_SHADE)
	{
		m_strFilename = "Revolver_moni_shade.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_STEN_GUN_SHADE_2)
	{
		m_strFilename = "Sten_gun_shade_2.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_TS23)
	{
		m_strFilename = "TS23.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_UMG)
	{	m_strFilename = "Umg.png";
		this->initWithFile(m_strFilename);
	}
}

/*virtual*/ void WeaponGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateWeapon)
	{
		case Monster::StateWeapon::WEAPON_STATE_FIRE:
		{
			if (hero.m_graphiComponentHeroBullet->GetSpeedBullet() != m_speedBullet)
			{
				hero.m_graphiComponentHeroBullet->SetSpeedBullet(m_speedBullet);
			}

			this->setPosition(hero.m_graphicComponentHero->getPosition().x, hero.m_graphicComponentHero->getPosition().y - 18);
															
			break;
		}
		case Monster::StateWeapon::WEAPON_STATE_REST:
		{	
			this->setPosition(hero.m_graphicComponentHero->getPosition().x, hero.m_graphicComponentHero->getPosition().y - 18);

			break;
		}
		case Monster::StateWeapon::WEAPON_CHECK_QUENTITY_BULLET:
		{
			if (m_quentityBullet <= 0)
			{
				hero.m_stateWeapon = Monster::StateWeapon::WEAPON_STATE_DEATH;
			}
			else
			{
				hero.m_stateWeapon = Monster::StateWeapon::WEAPON_STATE_FIRE;
			}

			break;
		}
		case Monster::StateWeapon::WEAPON_STATE_DEATH:
		{
			for (int i = 0; i < hero.m_vecGraphicComponentWeapon.size(); i++)
			{
				if (!hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->GetQuentityBullet())
				{
					hero.m_vecGraphicComponentWeapon.erase(hero.m_vecGraphicComponentWeapon.begin() + i);
					break;
				}
			}

			this->removeFromParentAndCleanup(true);
			hero.m_stateWeapon = Monster::StateWeapon::WEAPON_STATE_REST;

			break;
		}
	default:
		break;
	}

	return;
}

/*virtual*/ void WeaponGraphicComponent::SetSpeedBullet(int speed)
{

}

/*virtual*/ int WeaponGraphicComponent::GetSpeedBullet() const
{
	return 2;
}

/*virtual*/ void WeaponGraphicComponent::DescreaseQuentityBullet()
{
	--m_quentityBullet;
}

/*virtual*/ int WeaponGraphicComponent::GetQuentityBullet() const
{
	return m_quentityBullet;
}

/*virtual*/ int WeaponGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ int WeaponGraphicComponent::GetHealth() const
{
	return 1;
}

/*virtual*/ std::string WeaponGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ bool WeaponGraphicComponent::Dead(int wounded)
{
	return true;
}

/*virtual*/ void WeaponGraphicComponent::ChangeCoins(int coins)
{

}

/*virtual*/ bool WeaponGraphicComponent::Winner() const
{
	return true;
}

/*virtual*/ int WeaponGraphicComponent::GetValue() const
{
	return 2;
}

/*virtual*/ void WeaponGraphicComponent::ChangeHealth(int health)
{

}

WeaponGraphicComponent::~WeaponGraphicComponent()
{

}