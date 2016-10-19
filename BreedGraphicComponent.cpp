#include "BreedGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

const int CNT_BEGIN_VALUE_FIRE_ENEMY = 3;
const int CNT_BEGIN_VALUE_SPEED_MOVE = 1;
const int CNT_BEGIN_VALUE_SHOT_IN_HERO = 10;

using namespace std;

BreedGraphicComponent::BreedGraphicComponent(int attack, int health, const std::string& typeObject)
											: m_attack(attack),
											  m_health(health),
											  m_typeObject(typeObject)
{
	m_stateEnemy = StateEnemy::ENEMY_STATE_MOVE;

	m_BeginSecond			= GetTime();
	m_FireSecond			= CNT_BEGIN_VALUE_FIRE_ENEMY;
	m_SpeedMove				= CNT_BEGIN_VALUE_SPEED_MOVE;
	m_PositionXShotInHero	= CNT_BEGIN_VALUE_SHOT_IN_HERO;

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		SetPropertiesEnemy("res/Stones/rock1.png", CNT_TIME_SHOT_STONE_ROCK_1, 1, 5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		SetPropertiesEnemy("res/Stones/rock2.png", CNT_TIME_SHOT_STONE_ROCK_2, 2, 10);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		SetPropertiesEnemy("res/Stones/rock3.png", CNT_TIME_SHOT_STONE_ROCK_3, 3, 15);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		SetPropertiesEnemy("res/Stones/rock4.png", CNT_TIME_SHOT_STONE_ROCK_4, 4, 20);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		SetPropertiesEnemy("res/Stones/rock5.png", CNT_TIME_SHOT_STONE_ROCK_5, 5, 25);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		SetPropertiesEnemy("res/Stones/rock6.png", CNT_TIME_SHOT_STONE_ROCK_6, 6, 5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		SetPropertiesEnemy("res/Stones/rock7.png", CNT_TIME_SHOT_STONE_ROCK_7, 2, 10);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		SetPropertiesEnemy("res/Stones/rock8.png", CNT_TIME_SHOT_STONE_ROCK_8, 3, 15);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_9)
	{
		SetPropertiesEnemy("res/Stones/rock9.png", CNT_TIME_SHOT_STONE_ROCK_9, 4, 25);
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

	m_stateEnemy = StateEnemy::ENEMY_STATE_NOTHING;

	m_BeginSecond = GetTime();

	if (m_typeObject == CNT_NAME_ENEMY_ROCK_1)
	{
		SetPropertiesEnemy("res/Stones/rock1.png", CNT_TIME_SHOT_STONE_ROCK_1, 1, 5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		SetPropertiesEnemy("res/Stones/rock2.png", CNT_TIME_SHOT_STONE_ROCK_2, 2, 10);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		SetPropertiesEnemy("res/Stones/rock3.png", CNT_TIME_SHOT_STONE_ROCK_3, 3, 15);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		SetPropertiesEnemy("res/Stones/rock4.png", CNT_TIME_SHOT_STONE_ROCK_4, 4, 20);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		SetPropertiesEnemy("res/Stones/rock5.png", CNT_TIME_SHOT_STONE_ROCK_5, 5, 25);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		SetPropertiesEnemy("res/Stones/rock6.png", CNT_TIME_SHOT_STONE_ROCK_6, 6, 5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		SetPropertiesEnemy("res/Stones/rock7.png", CNT_TIME_SHOT_STONE_ROCK_7, 2, 10);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		SetPropertiesEnemy("res/Stones/rock8.png", CNT_TIME_SHOT_STONE_ROCK_8, 3, 15);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_9)
	{
		SetPropertiesEnemy("res/Stones/rock9.png", CNT_TIME_SHOT_STONE_ROCK_9, 4, 25);
	}

	auto physicsBody = PhysicsBody::createBox(this->getContentSize());
	physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setRotationEnable(true);

	srand(time(NULL));
	physicsBody->setTag(rand() % 1000000 + 1);

	this->setPhysicsBody(physicsBody);
}

// ***for future targets*** //
/*void BreedGraphicComponent::LoadTimeForShot()
{
	if (m_mapTimeShot.size())
	{
		return;
	}

	for (int i = 0; i < 12; i++)
	{
		m_mapTimeShot[i, 0] = rand() % 20 - i + 5;
		m_mapTimeShot[i, 1] = rand() % 30 - i + 5;
		m_mapTimeShot[i, 2] = rand() % 15 - i + 5;
		m_mapTimeShot[i, 3] = rand() % 36 - i + 5;
		m_mapTimeShot[i, 4] = rand() % 15 - i + 5;
		m_mapTimeShot[i, 5] = rand() % 14 - i + 5;
		m_mapTimeShot[i, 6] = rand() % 20 - i + 2;
		m_mapTimeShot[i, 7] = rand() % 20 - i + 5;
		m_mapTimeShot[i, 8] = rand() % 15 - i + 5;
		m_mapTimeShot[i, 9] = rand() % 14 - i + 5;
	}
}*/

void BreedGraphicComponent::SetPropertiesEnemy(const std::string& i_filename, const int& i_timeShot, const int& i_speedMove, const int& i_positionXShot)
{
	this->initWithFile(i_filename);
	int _randValueForFire = rand() % i_timeShot - GameScene::m_level + 1;
	m_FireSecond += _randValueForFire;
	m_SpeedMove += i_speedMove;
	m_PositionXShotInHero += i_positionXShot;
	m_value = _randValueForFire;
}

std::chrono::time_point<std::chrono::system_clock> BreedGraphicComponent::GetTime()
{
	std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now(); 

	return _time;
}

bool BreedGraphicComponent::StartFire(Monster& hero)
{
	if ((int)std::chrono::duration<double>(GetTime() - m_BeginSecond).count() == m_FireSecond)
	{
		m_pointBeginPosition = this->getPosition();
		hero.m_objectMonster->ReleaseCell(this->getPosition());

		return true;
	}
	else
	{
		return false;
	}
}

/*virtual*/ void BreedGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (StartFire(hero))
	{
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
				if (this->getPositionX() <= hero.m_graphicComponentHero->getPositionX() + 50)
				{
					this->m_stateEnemy = BreedGraphicComponent::StateEnemy::ENEMY_STATE_FIRE;
				}
				else
				{
					Move();
				}
				break;
			}
			case StateEnemy::ENEMY_STATE_WOUNDED:
			{
				Wounded();
				break;
			}
			case StateEnemy::ENEMY_STATE_DEATH:
			{
				this->removeFromParentAndCleanup(true);
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
	this->setPositionX(this->getPositionX() - m_SpeedMove);
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

BreedGraphicComponent::~BreedGraphicComponent()
{
	CCLOG("destructor breedgraphic");
}