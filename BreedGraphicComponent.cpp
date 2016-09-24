#include "BreedGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"
#include <time.h>

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


	time_t timer;
	struct tm y2k = { 0 };

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	m_BeginSecond = difftime(timer, mktime(&y2k));

	m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE;

	auto physicsBody = PhysicsBody::createBox(this->getContentSize());
	physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);

	srand(time(NULL));
	physicsBody->setTag(rand() % 1000000 + 1);

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
	physicsBody->setTag(breed.getTag());
	this->setPhysicsBody(physicsBody);
}

/*virtual*/ void BreedGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	time_t timer;
	struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	if (difftime(timer, mktime(&y2k)) == m_FireSecond)
	{
		this->m_stateEnemy = StateEnemy::ENEMY_STATE_FIRE;
	}

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
	Point _position = this->getPosition();
	_position.x -= CNT_SPEED_STONE;

	this->setPosition(_position);
}

void BreedGraphicComponent::Move()
{
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
	if (++m_countDefaultSpriteInDeath == m_vecDefaultNamesDeath.size())
	{
		return true;
	}
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecDefaultNamesDeath[m_countDefaultSpriteInDeath]));

	return false;
}

BreedGraphicComponent::~BreedGraphicComponent()
{

}