#include "PhysicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "HeroGraphicComponent.h"
#include "constants.h"
#include "GameOverScene.h"

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
		case StatePhysic::STATE_WOUNDED_ENEMY:
		{		
			for (int i = 0; i < hero.m_objectMonster->m_vecComponentEnemy.size(); i++)
			{
				auto body =  hero.m_objectMonster->m_vecComponentEnemy[i]->getPhysicsBody();
				if (body->getTag() == m_TagEnemy)
				{
					m_coin = hero.m_objectMonster->m_vecComponentEnemy[i]->GetValue();
					hero.m_objectMonster->ReleaseCell(hero.m_objectMonster->m_vecComponentEnemy[i]->getPosition());
					hero.m_objectMonster->m_vecComponentEnemy[i]->removeFromParentAndCleanup(true);
					hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin() + i);
				}
			}
				
			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_REST;
			hero.m_graphiComponentHeroBullet->setVisible(false);
			hero.m_graphiComponentHeroBullet->setPosition(Point(-10, -10));	

			m_TagEnemy = 0;
			this->m_statePhysic = StatePhysic::STATE_NOTHING;
			
			hero.m_graphicComponentHero->ChangeCoins(m_coin);
			m_coin = 0;
			if (hero.m_graphicComponentHero->Winner())
			{
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WINNER;
			}

			break;
		}
		case StatePhysic::STATE_WOUNDED_HERO:
		{
			for (int i = 0; i < hero.m_objectMonster->m_vecComponentEnemy.size(); i++)
			{
				auto body =  hero.m_objectMonster->m_vecComponentEnemy[i]->getPhysicsBody();
				if (body->getTag() == m_TagEnemy)
				{
					m_damage = hero.m_objectMonster->m_vecComponentEnemy[i]->GetAttack();
					hero.m_objectMonster->m_vecComponentEnemy[i]->removeFromParentAndCleanup(true);
					hero.m_objectMonster->ReleaseCell(hero.m_objectMonster->m_vecComponentEnemy[i]->getPosition());
					hero.m_objectMonster->m_vecComponentEnemy.erase(hero.m_objectMonster->m_vecComponentEnemy.begin() + i);
					break;
				}
			}

			m_TagEnemy = 0;
			this->m_statePhysic = StatePhysic::STATE_NOTHING;

			if (hero.m_graphicComponentHero->Dead(m_damage))
			{
				m_damage = 0;
				hero.m_stateHero	= Monster::StateHero::HERO_STATE_DEATH;
				hero.m_stateBullet	= Monster::StateBullet::BULLET_STATE_DEATH;
				hero.m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_DEATH;
				hero.m_stateEnemy	= Monster::StateEnemys::ENEMY_STATE_DEATH;
				hero.m_stateBonus	= Monster::StateBonus::BONUS_DEATH;

				srand(time(NULL));
				auto reScene = TransitionFade::create(1.0f, GameOverScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
				Director::getInstance()->replaceScene(reScene);
			}
			else
			{
				m_damage = 0;
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WOUNDED;
			}

			break;
		}
		case StatePhysic::STATE_TARGET_BONUS:
		{	
			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_TARGET;

			if (m_TagBonus <= CNT_TYPE_OBJECT_CASKET_CLOTHES)
			{
				hero.m_graphicComponentHero->ChangeCoins(50);
				scene.m_bonusGraphicComponent->m_showAnimation = true;
			}
			else if (m_TagBonus <= CNT_TYPE_OBJECT_WEAPON_UMG)	// last object for weapon
			{
				hero.AddWeapon(m_TagBonus);
				scene.m_bonusGraphicComponent->setVisible(false);
				scene.m_bonusGraphicComponent->setPosition(-500, -500);
				scene.m_bonusGraphicComponent->m_actived = false;
			}
			else
			{
				hero.AddBullet(m_TagBonus);
				scene.m_bonusGraphicComponent->setVisible(false);
				scene.m_bonusGraphicComponent->setPosition(-500, -500);
				scene.m_bonusGraphicComponent->m_actived = false;
			}

			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_REST;
			hero.m_graphiComponentHeroBullet->setVisible(false);
			hero.m_graphiComponentHeroBullet->setPosition(Point(-10, -10));

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