#include "Monster.h"
#include "BotBulletGraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "GameObjectMonster.h"

BotBulletGraphicComponent::BotBulletGraphicComponent(int i_ID, int attack, const std::string& typeObject)
														:	m_ID			(i_ID),
															m_attack		(attack),
															m_typeObject	(typeObject)
{
	m_visibleSize	= Director::getInstance()->getVisibleSize();
	m_pointBegin	= Point::ZERO;
	m_speed			= CNT_SPEED_BULLET;	
	
	this->initWithFile("res/Bullets/Meteor1.png");
	this->setScale(m_visibleSize.width / this->getContentSize().width / 25,
		m_visibleSize.height / this->getContentSize().height / 25);

	srand(time(NULL));
	int _randTag = rand() % 100000 + 0;

	auto physicBody = PhysicsBody::createBox(this->getBoundingBox().size);
	physicBody->setContactTestBitmask(true);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BOT_BULLET_COLLISION_BITMASK);
	physicBody->setTag(_randTag);

	this->setPhysicsBody(physicBody);
}

BotBulletGraphicComponent::BotBulletGraphicComponent(BotBulletGraphicComponent& bullet)
{
	this->m_attack		= bullet.GetAttack();
	this->m_typeObject	= bullet.GetTypeObject();
	this->m_position	= cocos2d::Point::ZERO;

	auto physicBody = PhysicsBody::createBox(this->getContentSize());
	physicBody->setContactTestBitmask(true);
	physicBody->setCollisionBitmask(BOT_BULLET_COLLISION_BITMASK);

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

void BotBulletGraphicComponent::ChangeState(const StateBullet newState)
{
	m_stateBullet = newState;
}

/*virtual*/ void BotBulletGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (!this->getParent())
	{
		scene.addChild(this);
	}

	switch (m_stateBullet)
	{
		case StateBullet::STATE_FIRE:
		{
			if (this->getPositionX() > 0)	// while visible on screen
			{
				this->setPositionX(this->getPositionX() - m_speed);
			}
			else
			{
				/*for (int i = 0; i < hero.m_objectMonster->m_vecComponentEnemyAirplane.size(); i++)
				{
					if (m_vecGraphicComponentBullet[i]->m_GraphicComponent->GetID() == m_ID)
					{
						hero.m_vecGraphicComponentBullet.erase(hero.m_vecGraphicComponentBullet.begin() + i);
						this->removeAllChildrenWithCleanup(true);
						this->getPhysicsBody()->removeFromWorld();
					}
				}*/
			}

			break;
		}
		case StateBullet::STATE_DEATH:
		{
			this->removeAllChildrenWithCleanup(true);
	
			break;
		}
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

BotBulletGraphicComponent::~BotBulletGraphicComponent()
{
	CCLOG("destructor botbullet");
}