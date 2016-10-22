#include "WeaponGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

WeaponGraphicComponent::WeaponGraphicComponent(int attack, const std::string& typeObject)
												: m_attack		(attack),
												  m_typeObject	(typeObject)
{
	this->setName(m_typeObject);

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	Size _sizeWeapon  = this->getContentSize();

	this->setScale(_visibleSize.width / _sizeWeapon.width / 12,
		_visibleSize.height / _sizeWeapon.height / 10);
}

WeaponGraphicComponent::WeaponGraphicComponent(WeaponGraphicComponent& weapon)
{
	this->m_attack		= weapon.GetAttack();
	this->m_typeObject	= weapon.GetTypeObject();
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

/*virtual*/ std::string& WeaponGraphicComponent::GetFileName()
{
	return m_strFilename;
}

WeaponGraphicComponent::~WeaponGraphicComponent()
{
	CCLOG("destructor weapongraphic");
}

/** List tasks on 15:10:2016**/
/*
	- Full working Weapon:
			- AddWeapon();
			- GetIndexActiveWeapon();
	- transition between levels;
	- save from previous level;
	- STATE_DEATH for all objects;
*/