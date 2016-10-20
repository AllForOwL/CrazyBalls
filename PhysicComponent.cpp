#include "PhysicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "HeroGraphicComponent.h"
#include "constants.h"
#include "GameOverScene.h"
#include "BonusGraphicComponent.h"
#include "AirplaneEnemyGraphicComponent.h"

PhysicComponent::PhysicComponent()
{
	m_statePhysic			= STATE_NOTHING;
	m_countElementInVector	= 0;
	m_tagForDelete			= 0;
	m_TagEnemy				= 0;
	m_damage				= 0;
	m_coin					= 0;
}

void PhysicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (m_statePhysic)
	{
		case StatePhysic::STATE_WOUNDED_ENEMY:	// when bullet hit in enemy
		{
			int _coinForEnemy = hero.m_objectMonster->GetCoinForEnemy(m_TagBullet);
			hero.m_graphicComponentHero->ChangeCoins(_coinForEnemy);
		
			int _indexEnemy			= hero.m_objectMonster->GetIndexEnemyForRemove(m_TagEnemy);
			int _temp				= hero.m_objectMonster->RemoveAndCleanEnemy(_indexEnemy);

			hero.RemoveBullet(m_TagBullet);

			this->m_statePhysic = StatePhysic::STATE_NOTHING;
			m_TagEnemy	= 0;
			m_TagBullet = 0;

			break;
		}
		case StatePhysic::STATE_WOUNDED_HERO:
		{
			hero.m_objectMonster->RemoveBullet(m_TagEnemy);

			hero.CauseDamage(50);
			m_TagEnemy = 0;
			this->m_statePhysic = StatePhysic::STATE_NOTHING;

			break;
		}
		case StatePhysic::STATE_TARGET_BONUS:
		{	
			this->m_statePhysic	= StatePhysic::STATE_NOTHING;

			break;
		}
		default:
			break;
	}
}

bool PhysicComponent::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* _a = contact.getShapeA()->getBody();
	PhysicsBody* _b = contact.getShapeB()->getBody();

	if (_a->getCollisionBitmask() == HERO_BULLET_COLLISION_BITMASK && _b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)
	{
		m_TagEnemy	= _b->getTag();
		m_TagBullet = _a->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_ENEMY;

		CCLOG("Collision enemy a");
	}
	else if (_a->getCollisionBitmask() == ENEMY_COLLISION_BITMASK && _b->getCollisionBitmask() == HERO_BULLET_COLLISION_BITMASK)
	{
		m_TagEnemy	= _a->getTag();
		m_TagBullet = _b->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_ENEMY;

		CCLOG("Collision enemy b");
	}
	if (_a->getCollisionBitmask() == BOT_BULLET_COLLISION_BITMASK && _b->getCollisionBitmask() == HERO_COLLISION_BITMASK)
	{
		m_TagEnemy = _a->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_HERO;

		CCLOG("Collision enemy a");
	}
	else if (_a->getCollisionBitmask() == HERO_COLLISION_BITMASK && _b->getCollisionBitmask() == BOT_BULLET_COLLISION_BITMASK)
	{
		m_TagEnemy = _b->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_HERO;

		CCLOG("Collision enemy b");
	}

	return true;
}

PhysicComponent::~PhysicComponent()
{
	CCLOG("destructor physiccomponent");
}