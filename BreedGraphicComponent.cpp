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

	m_BeginSecond = GetTime();

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		this->initWithFile("res/Stones/rock1.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_1;
		m_value = CNT_TIME_SHOT_STONE_ROCK_1;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_2;
		m_value = CNT_TIME_SHOT_STONE_ROCK_2;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		this->initWithFile("res/Stones/rock3.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_3;
		m_value = CNT_TIME_SHOT_STONE_ROCK_3;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		this->initWithFile("res/Stones/rock4.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_4;
		m_value = CNT_TIME_SHOT_STONE_ROCK_4;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		this->initWithFile("res/Stones/rock5.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_5;
		m_value = CNT_TIME_SHOT_STONE_ROCK_5;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		this->initWithFile("res/Stones/rock6.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_6;
		m_value = CNT_TIME_SHOT_STONE_ROCK_6;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		this->initWithFile("res/Stones/rock7.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_7;
		m_value = CNT_TIME_SHOT_STONE_ROCK_7;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		this->initWithFile("res/Stones/rock8.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_8;
		m_value = CNT_TIME_SHOT_STONE_ROCK_8;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_9)
	{
		this->initWithFile("res/Stones/rock9.png");
		m_FireSecond = m_BeginSecond + CNT_TIME_SHOT_STONE_ROCK_9;
		m_value = CNT_TIME_SHOT_STONE_ROCK_9;
	}

	auto physicsBody = PhysicsBody::createBox(this->getContentSize());
	physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setRotationEnable(true);

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

double BreedGraphicComponent::GetTime()
{
	time_t _timer;
	struct tm _y2k = { 0 };

	_y2k = { 0 };
	_y2k.tm_hour = 0;   _y2k.tm_min = 0; _y2k.tm_sec = 0;
	_y2k.tm_year = 100; _y2k.tm_mon = 0; _y2k.tm_mday = 1;
	time(&_timer);  /* get current time; same as: timer = time(NULL)  */

	return difftime(_timer, mktime(&_y2k));
}

/*virtual*/ void BreedGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (GetTime() == m_FireSecond)
	{
		m_pointBeginPosition = this->getPosition();
		hero.m_objectMonster->ReleaseCell(this->getPosition());

		this->m_stateEnemy = StateEnemy::ENEMY_STATE_FIRE;
	}

	switch (this->m_stateEnemy)
	{
			case StateEnemy::ENEMY_STATE_FIRE:
			{
				Fire(hero.m_graphicComponentHero->getPosition());
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

void BreedGraphicComponent::Fire(Point i_position)
{
	Size _visibleSize	= Director::getInstance()->getVisibleSize();
	Size _size			= this->getContentSize();

	Point _targetPoint	= i_position;
	Point _normalized	= ccpNormalize(ccpSub(_targetPoint, this->getPosition()));
	float _angle		= CC_RADIANS_TO_DEGREES(atan2f(_normalized.y, -_normalized.x));

	Point _myPosition = ccpAdd(this->getPosition(), ccpMult(_normalized, CNT_SPEED_STONE));

	this->setPosition(_myPosition);
	this->setRotation(_angle);
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

/*virtual*/ int BreedGraphicComponent::GetValue() const
{
	return m_value;
}

/*virtual*/ void BreedGraphicComponent::ChangeCoins(int coins)
{

}

/*virtual*/ bool BreedGraphicComponent::Winner() const
{
	return true;
}

BreedGraphicComponent::~BreedGraphicComponent()
{

}