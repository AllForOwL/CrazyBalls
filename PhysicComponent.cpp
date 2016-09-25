#include "PhysicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "HeroGraphicComponent.h"
#include "constants.h"

PhysicComponent::PhysicComponent()
{
	m_statePhysic			= STATE_NOTHING;
	m_countElementInVector	= 0;
	m_tagForDelete			= 0;
	m_TagEnemy				= 0;
}

void PhysicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (m_statePhysic)
	{
		case StatePhysic::STATE_WOUNDED_ENEMY:
		{
			//if (hero.m_objectMonster->m_vecComponentEnemy[m_TagEnemy]->Dead(hero.m_graphiComponentHeroBullet->GetAttack()))
			//{
				//hero.m_objectMonster->m_vecComponentEnemy[m_TagEnemy]->removeFromParentAndCleanup(true);
				//hero.m_objectMonster->m_vecComponentEnemy;
				
				for (int i = 0; i < hero.m_objectMonster->m_vecComponentEnemy.size(); i++)
				{
					auto body =  hero.m_objectMonster->m_vecComponentEnemy[i]->getPhysicsBody();
					if (body->getTag() == m_TagEnemy)
					{
						hero.m_objectMonster->m_vecComponentEnemy[i]->removeFromParentAndCleanup(true);
						hero.m_objectMonster->ReleaseCell(hero.m_objectMonster->m_vecComponentEnemy[i]->getPosition());
						hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin() + i);
					}
				}
				//hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin(), hero.m_objectMonster->m_vecComponentEnemy.end(), m_TagEnemy);
				hero.m_graphiComponentHeroBullet->setVisible(false);
				hero.m_graphiComponentHeroBullet->setPosition(hero.m_graphicComponentHero->getPosition());

				m_TagEnemy = 0;
				this->m_statePhysic = StatePhysic::STATE_NOTHING;
			//}
			//else
			//{
			//	hero.m_graphiComponentHeroBullet->removeFromParentAndCleanup(true);
			//	this->m_statePhysic = StatePhysic::STATE_NOTHING;
			//}
			break;
		}
		case StatePhysic::STATE_WOUNDED_HERO:
		{
			/*if (hero.m_graphicComponentHero->Dead(hero.m_objectMonster->m_vecComponentBullet[0]->GetAttack()))
			{
				hero.m_graphicComponentHero->removeFromParentAndCleanup(true);
				hero.m_graphicComponentHeroWeapon->removeFromParentAndCleanup(true);
				hero.m_objectMonster->m_vecComponentBullet[0]->removeFromParentAndCleanup(true);
				m_statePhysic = StatePhysic::STATE_NOTHING;
			}
			else
			{
				hero.m_objectMonster->m_vecComponentBullet[0]->removeFromParentAndCleanup(true);
				m_statePhysic = StatePhysic::STATE_NOTHING;
			}*/
						
			for (int i = 0; i < hero.m_objectMonster->m_vecComponentEnemy.size(); i++)
			{
				auto body =  hero.m_objectMonster->m_vecComponentEnemy[i]->getPhysicsBody();
				if (body->getTag() == m_TagEnemy)
				{
					hero.m_objectMonster->m_vecComponentEnemy[i]->removeFromParentAndCleanup(true);
					hero.m_objectMonster->ReleaseCell(hero.m_objectMonster->m_vecComponentEnemy[i]->getPosition());
					hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin() + i);
				}
			}
			//hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin(), hero.m_objectMonster->m_vecComponentEnemy.end(), m_TagEnemy);
			hero.m_graphiComponentHeroBullet->setVisible(false);
			hero.m_graphiComponentHeroBullet->setPosition(hero.m_graphicComponentHero->getPosition());

			m_TagEnemy = 0;
			this->m_statePhysic = StatePhysic::STATE_NOTHING;


			hero.m_stateHero = Monster::StateHero::HERO_STATE_WOUNDED;

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

	if (_a->getCollisionBitmask() == ENEMY_COLLISION_BITMASK && _b->getCollisionBitmask() == BULLET_COLLISION_BITMASK)
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