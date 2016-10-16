#include "AirplaneEnemyGraphicComponent.h"
#include "BotBulletGraphicComponent.h"
#include "constants.h"

AirplaneEnemyGraphicComponent::AirplaneEnemyGraphicComponent(const std::string& i_typeObject)
																: m_typeObject(i_typeObject)
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	DetermineTypeObject();

	m_stateAirplane = StateAirplane::STATE_REST;

	this->schedule(schedule_selector(AirplaneEnemyGraphicComponent::SetStateCreateBullets), m_timeSpawnShot);
}

/*virtual*/ void AirplaneEnemyGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (m_stateAirplane)
	{
		case StateAirplane::STATE_CREATE_BULLETS:
		{
			CreateBullets();
			break;
		}
		case StateAirplane::STATE_MOVE:
		{
			for (int i = 0; i < m_vecBullet.size(); i++)
			{
				m_vecBullet[i]->Update(hero, scene);
			}
			for (int i = 0; i < m_vecBullet.size(); i++)
			{
				if (m_vecBullet[i]->getPhysicsBody()->getTag() == -1)
				{
					m_vecBullet.erase(m_vecBullet.begin() + i);
				}
			}
			Move();

			break;
		}
		case StateAirplane::STATE_ATTACK:
		{
			break;
		}
		case StateAirplane::STATE_DEATH:
		{
			break;
		}
	default:
		break;
	}
}

void AirplaneEnemyGraphicComponent::Move()
{
	this->setPositionX(this->getPositionX() - 1);
}

void AirplaneEnemyGraphicComponent::CreateBullets()
{
	srand(time(NULL));
	int _IDTopBullet = rand() % 100000 + 0;

	BotBulletGraphicComponent* _bulletTopPosition = new BotBulletGraphicComponent(_IDTopBullet, 120, CNT_NAME_BULLET_POSITION_TOP);
	_bulletTopPosition->ChangeState(BotBulletGraphicComponent::StateBullet::STATE_FIRE);
	Point m_pointBegin = Point(this->getPositionX() - (this->getBoundingBox().size.width / 2),
		this->getPositionY() + (this->getBoundingBox().size.height / 2)
		);
	_bulletTopPosition->setPosition(m_pointBegin);
	_bulletTopPosition->setVisible(false);


	int _IDBottomBullet = rand() % 100000 + 0;
	BotBulletGraphicComponent* _bulletBottomPosition = new BotBulletGraphicComponent(_IDBottomBullet, 120, CNT_NAME_BULLET_POSITION_BOTTOM);
	_bulletBottomPosition->ChangeState(BotBulletGraphicComponent::StateBullet::STATE_FIRE);
	m_pointBegin = Point(this->getPositionX() - (this->getBoundingBox().size.width / 2),
		this->getPositionY() - (this->getBoundingBox().size.height / 2)
		);
	_bulletBottomPosition->setPosition(m_pointBegin);
	_bulletBottomPosition->setVisible(false);


	m_vecBullet.push_back(_bulletTopPosition);
	m_vecBullet.push_back(_bulletBottomPosition);

	m_stateAirplane = StateAirplane::STATE_MOVE;
}

void AirplaneEnemyGraphicComponent::SetStateCreateBullets(float dt)
{
	m_stateAirplane = StateAirplane::STATE_CREATE_BULLETS;
}

void AirplaneEnemyGraphicComponent::DetermineTypeObject()
{
	if (m_typeObject == CNT_NAME_ENEMY_BLACK_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack1.png", CNT_ATTACK_ENEMY_BLACK_1, 
			CNT_ARMOR_ENEMY_BLACK_1, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLACK_1);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack2.png", CNT_ATTACK_ENEMY_BLACK_2, 
			CNT_ARMOR_ENEMY_BLACK_2, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLACK_2);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack3.png", CNT_ATTACK_ENEMY_BLACK_3, 
			CNT_ARMOR_ENEMY_BLACK_3, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLACK_3);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack4.png", CNT_ATTACK_ENEMY_BLACK_4, 
			CNT_ARMOR_ENEMY_BLACK_4, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLACK_4);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack5.png", CNT_ATTACK_ENEMY_BLACK_5, 
			CNT_ARMOR_ENEMY_BLACK_5, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLACK_5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue1.png", CNT_ATTACK_ENEMY_BLUE_1, 
			CNT_ARMOR_ENEMY_BLUE_1, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLUE_1);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue2.png", CNT_ATTACK_ENEMY_BLUE_2, 
			CNT_ARMOR_ENEMY_BLUE_2, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLUE_2);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue3.png", CNT_ATTACK_ENEMY_BLUE_3, 
			CNT_ARMOR_ENEMY_BLUE_3, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLUE_3);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue4.png", CNT_ATTACK_ENEMY_BLUE_4, 
			CNT_ARMOR_ENEMY_BLUE_4, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLUE_4);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue5.png", CNT_ATTACK_ENEMY_BLUE_5, 
			CNT_ARMOR_ENEMY_BLUE_5, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_BLUE_5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen1.png", CNT_ATTACK_ENEMY_GREEN_1, 
			CNT_ARMOR_ENEMY_GREEN_1, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_GREEN_1);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen2.png", CNT_ATTACK_ENEMY_GREEN_2, 
			CNT_ARMOR_ENEMY_GREEN_2, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_GREEN_2);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen3.png", CNT_ATTACK_ENEMY_GREEN_3, 
			CNT_ARMOR_ENEMY_GREEN_3, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_GREEN_3);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen4.png", CNT_ATTACK_ENEMY_GREEN_4, 
			CNT_ARMOR_ENEMY_GREEN_4, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_GREEN_4);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen5.png", CNT_ATTACK_ENEMY_GREEN_5, 
			CNT_ARMOR_ENEMY_GREEN_5, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_GREEN_5);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed1.png", CNT_ATTACK_ENEMY_RED_1, 
			CNT_ARMOR_ENEMY_RED_1, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_RED_1);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed2.png", CNT_ATTACK_ENEMY_RED_2, 
			CNT_ARMOR_ENEMY_RED_2, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_RED_2);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed3.png", CNT_ATTACK_ENEMY_RED_3, 
			CNT_ARMOR_ENEMY_RED_3, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_RED_3);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed4.png", CNT_ATTACK_ENEMY_RED_4, 
			CNT_ARMOR_ENEMY_RED_4, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_RED_4);
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed5.png", CNT_ATTACK_ENEMY_RED_5, 
			CNT_ARMOR_ENEMY_RED_5, CNT_ENEMY_HEALTH, CNT_TIME_SPAWN_SHOT_RED_5);
	}
}

void AirplaneEnemyGraphicComponent::SetPropertiesAirplane(const std::string& i_filename, const int& i_attack, const int& i_armor, const int& i_health ,const int& i_spawnShot)
{
	this->initWithFile(i_filename);
	this->setScale(m_visibleSize.width / this->getContentSize().width / 12,
		m_visibleSize.height / this->getContentSize().height / 10);
	this->setRotation(90.0);
	this->setVisible(true);

	int _randTagForPhysicCollision = rand() % 100000 + 0;
	this->setTag(_randTagForPhysicCollision);

	this->m_timeSpawnShot	= i_spawnShot;
	this->m_attack			= i_attack;
	this->m_armor			= i_armor;
	this->m_health			= i_health;

	auto physicBodyEnemy = PhysicsBody::createBox(this->getBoundingBox().size);
	physicBodyEnemy->setContactTestBitmask(true);
	physicBodyEnemy->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyEnemy);
}

AirplaneEnemyGraphicComponent::AirplaneEnemyGraphicComponent(const AirplaneEnemyGraphicComponent& copyObject)
{
	this->m_attack		= copyObject.m_attack;
	this->m_armor		= copyObject.m_armor;
	this->m_health		= copyObject.m_health;
	this->m_typeObject	= copyObject.m_typeObject;
}

int AirplaneEnemyGraphicComponent::GetAttack() const
{
	return m_attack;
}

int AirplaneEnemyGraphicComponent::GetArmor() const
{
	return m_armor;
}

int AirplaneEnemyGraphicComponent::GetHealth() const
{
	return m_health;
}

std::string AirplaneEnemyGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

/*virtual*/  void AirplaneEnemyGraphicComponent::CauseDamage(const int& i_numberDamageHealth, const int& i_numberDamageArmor)
{
	m_health	-= i_numberDamageHealth;
	m_armor		-= i_numberDamageArmor;
}

