#include "Monster.h"
#include "PlayerBulletGraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "GameObjectMonster.h"

PlayerBulletGraphicComponent::PlayerBulletGraphicComponent(int attack, const std::string& typeObject)
																			: m_attack		(attack),
																			  m_typeObject	(typeObject)
{
	if (m_typeObject == CNT_NAME_BULLET_DEFAULT)
	{
		LoadBulletNormal();
		this->initWithFile(m_strFilename);
	}

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);

	this->setPhysicsBody(physicBody);
}

PlayerBulletGraphicComponent::PlayerBulletGraphicComponent(PlayerBulletGraphicComponent& bullet)
{
	this->m_attack		= bullet.GetAttack();
	this->m_typeObject	= bullet.GetTypeObject();
	this->m_position	= cocos2d::Point::ZERO;

	if (m_typeObject == CNT_NAME_BULLET_DEFAULT)
	{
		LoadBulletNormal();
		this->initWithFile(m_strFilename);
	}

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);

	this->setPhysicsBody(physicBody);
}

/*virtual*/ int PlayerBulletGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ int PlayerBulletGraphicComponent::GetHealth() const
{
	return 1;
}
/*virtual*/ std::string PlayerBulletGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ bool PlayerBulletGraphicComponent::Dead(int wounded)
{
	return true;
}

/*virtual*/ void PlayerBulletGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateBullet)
	{
		case Monster::StateBullet::BULLET_STATE_FIRE:
		{
			if (m_position == cocos2d::Point::ZERO)
			{
				m_position = hero.m_graphicComponentHeroWeapon->getPosition();
				m_position.x += 80;
			}
			else if (m_position < Director::getInstance()->getVisibleSize())
			{
				m_position.x += CNT_SPEED_BULLET;
			}
			else
			{
				m_position = Point::ZERO;
				hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_REST;
			}
			setPosition(m_position);

			break;
		}
		case Monster::StateBullet::BULLET_STATE_FIRE_UP:
		{
			if (m_position == cocos2d::Point::ZERO)
			{
				m_position = hero.m_graphicComponentHeroWeapon->getPosition();
			}
			else if (m_position < Director::getInstance()->getVisibleSize())
			{
				++m_position.x;
				m_position.y += 2;
			}
			else
			{
				m_position = Point::ZERO;
				hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_REST;
			}
			setPosition(m_position);

			break;
		}
		case Monster::StateBullet::BULLET_STATE_REST:
		{
			
			break;
		}
		default:
			break;
	}
}

void PlayerBulletGraphicComponent::LoadBulletNormal()
{
	m_position = Point::ZERO;
	m_strFilename = "res/Bullets/Bullet_normal.png";
}


/*virtual*/ void PlayerBulletGraphicComponent::ChangeCoins(int coins)
{

}

/*virtual*/ bool PlayerBulletGraphicComponent::Winner() const
{
	return true;
}

/*virtual*/ int PlayerBulletGraphicComponent::GetValue() const
{
	return 2;
}

PlayerBulletGraphicComponent::~PlayerBulletGraphicComponent()
{

}