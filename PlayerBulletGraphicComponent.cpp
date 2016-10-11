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
	m_speed = 8;
	m_position = Point(-10, -10);
	m_targetPoint = Point(Point::ZERO);
	this->setPosition(m_position);
	this->setVisible(false);

	if (m_typeObject == CNT_NAME_BULLET_DEFAULT)
	{
		LoadBulletNormal();
		this->initWithFile(m_strFilename);
	}

	this->setName(m_typeObject);

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	//physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	physicBody->setName("physics");

	this->setPhysicsBody(physicBody);
	m_isBody = true;
}

PlayerBulletGraphicComponent::PlayerBulletGraphicComponent(PlayerBulletGraphicComponent& bullet)
{
	this->m_attack		= bullet.GetAttack();
	this->m_typeObject	= bullet.GetTypeObject();
	this->m_position	= cocos2d::Point::ZERO;
	this->m_targetPoint = cocos2d::Point::ZERO;

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
			m_position = this->getPosition();

			if (m_position.x < 0)
			{
				int _indexActiveWeapon = hero.GetIndexActiveWeapon();

				this->setVisible(true);
				Vec2 _positionWeapon	= hero.m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->getPosition();
				hero.m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->DescreaseQuentityBullet();
				_positionWeapon.x		+= CNT_SPEED_BULLET;
				m_position				= _positionWeapon;
				this->setPosition(m_position);
			}
			else if (m_position.x > Director::getInstance()->getVisibleSize().width)
			{
				m_position = Point(-10, -10);
				this->setPosition(m_position);
				this->setVisible(false);
				hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_REST;
				hero.m_stateWeapon = Monster::StateWeapon::WEAPON_CHECK_QUENTITY_BULLET;
			}
			else
			{
				Size _visibleSize = Director::getInstance()->getVisibleSize();
				Size _size = this->getContentSize();

				Point _myPosition = Point(this->getPositionX() + CNT_SPEED_BULLET, this->getPositionY());
				this->setPosition(_myPosition);
			}

			break;
		}
		case Monster::StateBullet::BULLET_STATE_TARGET:
		{
			m_position = this->getPosition();
			m_position = Point::ZERO;
			this->setPosition(m_position);
			this->setVisible(false);

			break;
		}
		case  Monster::StateBullet::BULLET_STATE_DEATH:
		{
			this->removeFromParentAndCleanup(true);
			break;
		}
	}
}

/*virtual*/ void PlayerBulletGraphicComponent::SetTargetPointForBullet(cocos2d::Point point)
{
	m_targetPoint = point;
}

void PlayerBulletGraphicComponent::LoadBulletNormal()
{
	m_position = Point::ZERO;
	m_strFilename = "res/Bullets/Bullet_normal.png";
}

void PlayerBulletGraphicComponent::SetSpeedBullet(int speed)
{
	this->m_speed = speed;
}

int PlayerBulletGraphicComponent::GetSpeedBullet() const
{
	return this->m_speed;
}

/*virtual*/ void PlayerBulletGraphicComponent::ChangeCoins(int coins)
{
	
}

/*virtual*/ bool PlayerBulletGraphicComponent::Winner() const
{
	return true;
}

/*virtual*/ void PlayerBulletGraphicComponent::SetTargetPosition_YForHero(int target_y)
{

}

/*virtual*/ int PlayerBulletGraphicComponent::GetValue() const
{
	return 2;
}

/*virtual*/ void PlayerBulletGraphicComponent::DescreaseQuentityBullet()
{

}

/*virtual*/ int PlayerBulletGraphicComponent::GetQuentityBullet() const
{
	return 1;
}

/*virtual*/ void PlayerBulletGraphicComponent::ChangeHealth(int health)
{

}

PlayerBulletGraphicComponent::~PlayerBulletGraphicComponent()
{

}