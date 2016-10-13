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
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_AK47, "res/Weapons/AK47.png", 8, 50);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_GUN)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_GUN, "res/Weapons/Gun.png", 9, 15);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MI71)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_MI71, "res/Weapons/MI71.png", 10, 20);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MK15)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_MK15, "res/Weapons/MK15.png", 11, 25);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_REVOLVER_MONI_SHADE)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE, "res/Weapons/Revolver_moni_shade.png", 12, 30);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_STEN_GUN_SHADE_2)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2, "res/Weapons/Sten_gun_shade_2.png", 13, 35);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_TS23)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_TS23, "res/Weapons/TS23.png", 14, 40);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_UMG)
	{
		SetPropertiesWeapon(CNT_TYPE_OBJECT_WEAPON_UMG, "res/Weapons/Umg.png", 14, 45);
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

void WeaponGraphicComponent::SetPropertiesWeapon(const int& i_typeObject, const std::string& i_filename, const int& i_speedBullet, const int& i_quentityBullet)
{
	this->setTag(i_typeObject);
	m_strFilename = i_filename;
	this->initWithFile(i_filename);
	m_speedBullet = i_speedBullet;
	m_quentityBullet = i_quentityBullet;
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

/*virtual*/ std::string WeaponGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

WeaponGraphicComponent::~WeaponGraphicComponent()
{

}