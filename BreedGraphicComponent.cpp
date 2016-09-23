#include "BreedGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

BreedGraphicComponent::BreedGraphicComponent(int attack, int health, const std::string& typeObject)
											: m_attack(attack),
											  m_health(health),
											  m_typeObject(typeObject)
{
	m_stateEnemy = StateEnemy::ENEMY_STATE_NOTHING;

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		this->initWithFile("res/Stones/rock1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		this->initWithFile("res/Stones/rock3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		this->initWithFile("res/Stones/rock4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		this->initWithFile("res/Stones/rock5.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		this->initWithFile("res/Stones/rock6.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		this->initWithFile("res/Stones/rock7.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		this->initWithFile("res/Stones/rock8.png");
	}
	else
	{
		this->initWithFile("res/Stones/rock9.png");
	}

	auto physicsBody = PhysicsBody::createBox(this->getContentSize());
	physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setTag(m_health - 100);

	this->setPhysicsBody(physicsBody);
}

BreedGraphicComponent::BreedGraphicComponent(BreedGraphicComponent& breed)
{
	this->m_attack		= breed.GetAttack();
	this->m_health		= breed.GetHealth();
	this->m_typeObject	= breed.GetTypeObject();

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		this->initWithFile("res/Stones/rock1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		this->initWithFile("res/Stones/rock3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		this->initWithFile("res/Stones/rock4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		this->initWithFile("res/Stones/rock5.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		this->initWithFile("res/Stones/rock6.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		this->initWithFile("res/Stones/rock7.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		this->initWithFile("res/Stones/rock8.png");
	}
	else
	{
		this->initWithFile("res/Stones/rock9.png");
	}

	auto physicsBody = PhysicsBody::createBox(this->getContentSize());
	//physicsBody->setDynamic(false);
	physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setTag(m_health - 100);
	this->setPhysicsBody(physicsBody);
}

/*virtual*/ void BreedGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	/*if (this->getTag() != 0)
	{
		this->m_stateEnemy = StateEnemy::ENEMY_STATE_WOUNDED;
	}
	*/
	switch (this->m_stateEnemy)
	{
			case StateEnemy::ENEMY_STATE_FIRE:
			{
				Fire();			
				break;
			}
			case StateEnemy::ENEMY_STATE_MOVE:
			{
				Move();
				break;
			}
			case StateEnemy::ENEMY_STATE_WOUNDED:
			{
				Wounded();
				break;
			}
			case StateEnemy::ENEMY_STATE_DEATH:
			{
				if (Death())
				{
					hero.m_objectMonster->m_vecComponentEnemy.pop_back();
				}
				break;
			}
			default:
				break;
	}
}

/*virtual*/int BreedGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/int BreedGraphicComponent::GetHealth() const
{
	return m_health;
}

/*virtual*/std::string BreedGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/ bool BreedGraphicComponent::Dead(int wounded)
{
	m_health -= wounded;

	if (m_health < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BreedGraphicComponent::Fire()
{
	if (++m_countDefaultSpriteInFire == m_vecDefaultNamesFire.size())
	{
		m_countDefaultSpriteInFire = 0;
	}
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecDefaultNamesFire[m_countDefaultSpriteInFire]));
}

void BreedGraphicComponent::Move()
{
//	if (this->GetTypeObject() == CNT_NAME_ENEMY_TURRET)
//	{
//		return;
//	}

	if (++m_countDefaultSpriteInMove == m_vecDefaultNamesMove.size())
	{
		m_countDefaultSpriteInMove = 0;
	}
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecDefaultNamesMove[m_countDefaultSpriteInMove]));
}

void BreedGraphicComponent::Wounded()
{
	this->m_health -= getTag();

	if (m_health)
	{
		this->setTag(0);
	}
	else
	{
		this->m_stateEnemy = ENEMY_STATE_DEATH;
	}
}

bool BreedGraphicComponent::Death()
{
//	if (this->GetTypeObject() != CNT_NAME_ENEMY_TANK)
//	{
//		return true;
//	}

	if (++m_countDefaultSpriteInDeath == m_vecDefaultNamesDeath.size())
	{
		return true;
	}
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecDefaultNamesDeath[m_countDefaultSpriteInDeath]));

	return false;
}

void BreedGraphicComponent::LoadSpritesForSoldier()
{

}

void BreedGraphicComponent::LoadSpritesForTanks()
{
	
}

void BreedGraphicComponent::LoadSpritesForTurrets()
{
	
}

void BreedGraphicComponent::LoadSpritesForAirplanes()
{

}

BreedGraphicComponent::~BreedGraphicComponent()
{

}