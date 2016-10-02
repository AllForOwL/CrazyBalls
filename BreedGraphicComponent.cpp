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
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_1 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_2 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		this->initWithFile("res/Stones/rock3.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_3 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		this->initWithFile("res/Stones/rock4.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_4 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		this->initWithFile("res/Stones/rock5.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_5 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		this->initWithFile("res/Stones/rock6.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_6 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		this->initWithFile("res/Stones/rock7.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_7 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		this->initWithFile("res/Stones/rock8.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_8 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_9)
	{
		this->initWithFile("res/Stones/rock9.png");
		int _randValueForFire = rand() % CNT_TIME_SHOT_STONE_ROCK_9 - GameScene::m_level + 1;
		m_FireSecond = m_BeginSecond + _randValueForFire;
		m_value = _randValueForFire;
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
		this->initWithFile("res/Stones/rock1.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_1 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_2)
	{
		this->initWithFile("res/Stones/rock2.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_2 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_3)
	{
		this->initWithFile("res/Stones/rock3.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_3 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_4)
	{
		this->initWithFile("res/Stones/rock4.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_4 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_5)
	{
		this->initWithFile("res/Stones/rock5.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_5 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_6)
	{
		this->initWithFile("res/Stones/rock6.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_6 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_7)
	{
		this->initWithFile("res/Stones/rock7.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_7 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_8)
	{
		this->initWithFile("res/Stones/rock8.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_8 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
	}
	else if (m_typeObject == CNT_NAME_ENEMY_ROCK_9)
	{
		this->initWithFile("res/Stones/rock9.png");
		int _randValueForFire	= rand() % CNT_TIME_SHOT_STONE_ROCK_9 - GameScene::m_level + 1;
		m_FireSecond			= m_BeginSecond + _randValueForFire;
		m_value					= _randValueForFire;
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
				/*if (Death())
				{
					hero.m_objectMonster->m_vecComponentEnemy.pop_back();
				}*/
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

/*virtual*/ void BreedGraphicComponent::SetSpeedBullet(int speed)
{

}

/*virtual*/ int BreedGraphicComponent::GetSpeedBullet() const
{
	return 2;
}

/*virtual*/ void BreedGraphicComponent::DescreaseQuentityBullet()
{

}

/*virtual*/ int BreedGraphicComponent::GetQuentityBullet() const
{
	return 1;
}


BreedGraphicComponent::~BreedGraphicComponent()
{

}