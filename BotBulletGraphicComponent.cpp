#include "Monster.h"
#include "BotBulletGraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "GameObjectMonster.h"

BotBulletGraphicComponent::BotBulletGraphicComponent(int attack, const std::string& typeObject)
														: m_attack		(attack),
														  m_typeObject	(typeObject)
{
	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		this->initWithFile("res/Stones/rock1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
	}

	this->setPhysicsBody(physicBody);
}

BotBulletGraphicComponent::BotBulletGraphicComponent(BotBulletGraphicComponent& bullet)
{
	this->m_attack		= bullet.GetAttack();
	this->m_typeObject	= bullet.GetTypeObject();
	this->m_position	= cocos2d::Point::ZERO;

	if (m_typeObject == CNT_NAME_BULLET_DEFAULT)
	{
		LoadBulletNormal();
		this->initWithFile(m_strFilename);
	}
	else if (m_typeObject == CNT_NAME_BOMB)
	{
		LoadBomb();
		this->initWithFile(m_strFilename);
	}

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);

	this->setPhysicsBody(physicBody);
}

/*virtual*/int BotBulletGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/std::string BotBulletGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ int BotBulletGraphicComponent::GetHealth() const
{
	return 1;
}

/*virtual*/ bool BotBulletGraphicComponent::Dead(int wounded)
{
	return true;
}

/*virtual*/ void BotBulletGraphicComponent::SetSpeedBullet(int speed)
{

}
/*virtual*/ int BotBulletGraphicComponent::GetSpeedBullet() const
{
	return 2;
}

/*virtual*/ void BotBulletGraphicComponent::SetTargetPointForBullet(cocos2d::Point point)
{

}

/*virtual*/ void BotBulletGraphicComponent::SetTargetPosition_YForHero(int target_y)
{

}

/*virtual*/ void BotBulletGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_objectMonster->m_stateBullet)
	{
		case GameObjectMonster::StateBullet::STATE_FIRE:
		{
			Vec2 _position = this->getPosition();															
			this->setPosition(_position.x -= CNT_SPEED_BULLET, _position.y);
			this->setVisible(true);

			break;
		}
		case GameObjectMonster::StateBullet::STATE_FIRE_UP:
		{
			Vec2 _position = this->getPosition();
			Size _visibleSize = Director::getInstance()->getVisibleSize();

			if (_position.x >= _visibleSize.width / 2)
			{
				_position.y += 2;
				this->setPosition(--_position.x, _position.y);
			}
			else
			{
				_position.y -= 2;
				this->setPosition(--_position.x, _position.y);
			}

			break;
		}
		case GameObjectMonster::StateBullet::STATE_FIRE_BOMB:
		{
			break;
		}
		case GameObjectMonster::StateBullet::STATE_HIT_IN_TARGET:
		{
			hero.m_graphicComponentHero->setTag(this->GetAttack());
			this->removeFromParentAndCleanup(true);
			hero.m_objectMonster->m_vecComponentBullet.pop_back();

			break;
		}
		default:
			break;
	}
}

void BotBulletGraphicComponent::LoadBulletNormal()
{
	m_position = Point::ZERO;
	m_strFilename = "Bullet_normal.png";
}

void BotBulletGraphicComponent::LoadBomb()
{
	m_position = Point::ZERO;
	m_strFilename = "Bomb.png";
}


/*virtual*/ void BotBulletGraphicComponent::DescreaseQuentityBullet()
{

}

/*virtual*/ int BotBulletGraphicComponent::GetQuentityBullet() const
{
	return 1;
}

/*virtual*/ void BotBulletGraphicComponent::ChangeHealth(int health)
{

}

BotBulletGraphicComponent::~BotBulletGraphicComponent()
{

}