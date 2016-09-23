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
		m_strFilename = "AK47.png";
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
	{
		m_strFilename = "Umg.png";
		this->initWithFile(m_strFilename);
	}
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
	return;
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

WeaponGraphicComponent::~WeaponGraphicComponent()
{

}