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
		m_strFilename = "res/Weapons/AK47.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_GUN)
	{
		m_strFilename = "res/Weapons/Gun.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MI71)
	{
		m_strFilename = "res/Weapons/MI71.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_MK15)
	{
		m_strFilename = "res/Weapons/MK15.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_REVOLVER_MONI_SHADE)
	{
		m_strFilename = "res/Weapons/Revolver_moni_shade.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_STEN_GUN_SHADE_2)
	{
		m_strFilename = "res/Weapons/Sten_gun_shade_2.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_TS23)
	{
		m_strFilename = "res/Weapons/TS23.png";
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_WEAPON_UMG)
	{
		m_strFilename = "res/Weapons/Umg.png";
		this->initWithFile(m_strFilename);
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
	//this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_strFilename));
	this->setPosition(hero.m_graphicComponentHero->getPosition());

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

WeaponGraphicComponent::~WeaponGraphicComponent()
{

}