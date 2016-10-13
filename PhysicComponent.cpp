#include "PhysicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "HeroGraphicComponent.h"
#include "constants.h"
#include "GameOverScene.h"
#include "BonusGraphicComponent.h"

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
			int _indexEnemy			= hero.m_objectMonster->GetIndexEnemyForRemove(m_TagEnemy);
			int _coinForRemoveEnemy = hero.m_objectMonster->RemoveAndCleanEnemy(_indexEnemy);
			hero.m_graphicComponentHero->ChangeCoins(_coinForRemoveEnemy);
			hero.CheckHeroOnLevelCompete();

			this->m_statePhysic = StatePhysic::STATE_NOTHING;
			m_TagEnemy = 0;

			break;
		}
		case StatePhysic::STATE_WOUNDED_HERO:
		{
			int _indexEnemy			= hero.m_objectMonster->GetIndexEnemyForRemove(m_TagEnemy);
			int _damage				= hero.m_objectMonster->GetDamage(_indexEnemy);
			int _coinForRemoveEnemy = hero.m_objectMonster->RemoveAndCleanEnemy(_indexEnemy);
			
			hero.CauseDamage(_damage);

			m_TagEnemy = 0;
			this->m_statePhysic = StatePhysic::STATE_NOTHING;

			break;
		}
		case StatePhysic::STATE_TARGET_BONUS:
		{	
			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_TARGET;
			hero.m_stateWeapon = Monster::StateWeapon::WEAPON_CHECK_QUENTITY_BULLET;

			if (m_TagBonus == CNT_TYPE_OBJECT_CASKET_COINS)
			{
				hero.m_stateHero  = Monster::StateHero::HERO_STATE_TAKE_COIN;
				scene.m_bonusGraphicComponent->StartShowAnimation();
			}
			else if (m_TagBonus == CNT_TYPE_OBJECT_CASKET_POWER)
			{
				hero.m_stateHero  = Monster::StateHero::HERO_STATE_TAKE_POWER; 
				scene.m_bonusGraphicComponent->StartShowAnimation();
			}
			else if (m_TagBonus <= CNT_TYPE_OBJECT_WEAPON_UMG)	// last object for weapon
			{
				hero.AddWeapon(m_TagBonus);
				scene.m_bonusGraphicComponent->HideObject();
			}
			else if (m_TagBonus == CNT_TYPE_OBJECT_BULLET_NORMAL)
			{
				hero.AddBullet(m_TagBonus);
				scene.m_bonusGraphicComponent->HideObject();
			}

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

	if (_a->getCollisionBitmask() == BULLET_COLLISION_BITMASK && _b->getCollisionBitmask() == BONUS_COLLISION_BITMASK)
	{
		m_TagBonus = _b->getTag();
		this->m_statePhysic = StatePhysic::STATE_TARGET_BONUS;

		CCLOG("Collision bonus");
	}
	else if (_a->getCollisionBitmask() == BONUS_COLLISION_BITMASK && _b->getCollisionBitmask() == BULLET_COLLISION_BITMASK)
	{
		m_TagBonus = _a->getTag();
		this->m_statePhysic = StatePhysic::STATE_TARGET_BONUS;

		CCLOG("Collision bonus");
	}
	else if (_a->getCollisionBitmask() == ENEMY_COLLISION_BITMASK && _b->getCollisionBitmask() == BULLET_COLLISION_BITMASK)
	{
		m_TagEnemy = _a->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_ENEMY;

		CCLOG("Collision enemy a");
	}
	else if (_a->getCollisionBitmask() == BULLET_COLLISION_BITMASK && _b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)
	{
		m_TagEnemy = _b->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_ENEMY;

		CCLOG("Collision enemy b");
	}
	else if (_a->getCollisionBitmask() == ENEMY_COLLISION_BITMASK &&_b->getCollisionBitmask() == HERO_COLLISION_BITMASK)
	{
		m_TagEnemy = _a->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_HERO;

		CCLOG("Collision hero b");
	}
	else if (_a->getCollisionBitmask() == HERO_COLLISION_BITMASK &&_b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK)
	{
		m_TagEnemy = _b->getTag();
		this->m_statePhysic = StatePhysic::STATE_WOUNDED_HERO;

		CCLOG("Collision hero a");
	}

	return true;
}

PhysicComponent::~PhysicComponent()
{

}