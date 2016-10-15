#include "Monster.h"
#include "PlayerBulletGraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "GameObjectMonster.h"

//const int CNT_SPEED_BULLET = 8;

PlayerBulletGraphicComponent::PlayerBulletGraphicComponent(int i_ID, int attack, const std::string& typeObject)
																			:	m_ID			(i_ID),
																				m_attack		(attack),
																				m_typeObject	(typeObject)
{
	m_stateBullet = StateBullet::BULLET_STATE_REST;
	m_visibleSize = Director::getInstance()->getVisibleSize();

	m_speed = CNT_SPEED_BULLET;

	this->initWithFile("res/Bullets/Meteor1.png");
	this->setScale(m_visibleSize.width / this->getContentSize().width / 20,
		m_visibleSize.height / this->getContentSize().height / 20);


	auto physicBodyBullet = PhysicsBody::createBox(this->getContentSize());
	physicBodyBullet->setContactTestBitmask(true);
	physicBodyBullet->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyBullet);
}

PlayerBulletGraphicComponent::PlayerBulletGraphicComponent(PlayerBulletGraphicComponent& bullet)
{
	this->m_attack		= bullet.GetAttack();
	this->m_typeObject	= bullet.GetTypeObject();

	this->m_targetPoint = cocos2d::Point::ZERO;

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);

	this->setPhysicsBody(physicBody);
}

/*virtual*/ int PlayerBulletGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ std::string PlayerBulletGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ int PlayerBulletGraphicComponent::GetID() const
{
	return m_ID;
}

/*virtual*/ void PlayerBulletGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (!this->getParent())
	{
		scene.addChild(this);
		if (this->m_typeObject == CNT_NAME_BULLET_POSITION_TOP)
		{
			m_pointBegin = Point(hero.m_graphicComponentHero->getPositionX() + hero.m_graphicComponentHero->getBoundingBox().size.width,
				hero.m_graphicComponentHero->getPositionY() + (hero.m_graphicComponentHero->getBoundingBox().size.height / 2)
								);
			this->setPosition(m_pointBegin);
			this->setVisible(false);
		}
		else
		{
			m_pointBegin = Point(hero.m_graphicComponentHero->getPositionX() + hero.m_graphicComponentHero->getBoundingBox().size.width,
				hero.m_graphicComponentHero->getPositionY() - (hero.m_graphicComponentHero->getBoundingBox().size.height / 2)
				);
			this->setPosition(m_pointBegin);
			this->setVisible(false);
		}
	}

	switch (m_stateBullet)
	{
		case StateBullet::BULLET_STATE_FIRE:
		{
			if (this->getPosition() < m_visibleSize)	// while visible on screen
			{
				this->setPositionX(this->getPositionX() + m_speed);
			}
			else
			{
				for (int i = 0; i < hero.m_vecGraphicComponentBullet.size(); i++)
				{
					if (hero.m_vecGraphicComponentBullet[i]->m_GraphicComponent->GetID() == m_ID)
					{
						hero.m_vecGraphicComponentBullet.erase(hero.m_vecGraphicComponentBullet.begin() + i);
						m_stateBullet = StateBullet::BULLET_STATE_DEATH;
					}
				}
			}

			break;
		}
		case StateBullet::BULLET_STATE_TARGET:
		{
			/*m_position = this->getPosition();
			m_position = Point::ZERO;
			this->setPosition(m_position);
			this->setVisible(false);*/

			break;
		}
		case StateBullet::BULLET_STATE_DEATH:
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
//	m_position = Point::ZERO;
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

/*virtual*/ void PlayerBulletGraphicComponent::HideObject()
{
	this->setVisible(false);
	this->setPosition(Point(-10, -10));
}

void PlayerBulletGraphicComponent::ChangeStateBullet(const StateBullet& newState)
{
	m_stateBullet = newState;
}

PlayerBulletGraphicComponent::~PlayerBulletGraphicComponent()
{

}