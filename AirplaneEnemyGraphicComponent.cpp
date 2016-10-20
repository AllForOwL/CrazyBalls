#include <iostream>
#include "AirplaneEnemyGraphicComponent.h"
#include "BotBulletGraphicComponent.h"
#include "constants.h"
#include <GameScene.h>

typedef AirplaneEnemyGraphicComponent Airplane;

std::vector<Airplane::PropertiesAirplane> Airplane::m_vecAirplaneBlack(CNT_QUENTITY_LEVELS);
std::vector<Airplane::PropertiesAirplane> Airplane::m_vecAirplaneBlue(CNT_QUENTITY_LEVELS);
std::vector<Airplane::PropertiesAirplane> Airplane::m_vecAirplaneGreen(CNT_QUENTITY_LEVELS);
std::vector<Airplane::PropertiesAirplane> Airplane::m_vecAirplaneRed(CNT_QUENTITY_LEVELS);

AirplaneEnemyGraphicComponent::AirplaneEnemyGraphicComponent(const std::string& i_typeObject)
																: m_typeObject(i_typeObject)
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	DetermineTypeObject();

	m_stateAirplane = StateAirplane::STATE_MOVE;

	this->schedule(schedule_selector(AirplaneEnemyGraphicComponent::SetStateCreateBullets), m_timeSpawnShot);
}

/*virtual*/ void AirplaneEnemyGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (!this->getParent())
	{
		scene.addChild(this);
	}

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
				if (m_vecBullet[i]->getPositionX() < 0)
				{
					m_vecBullet[i]->removeFromParentAndCleanup(true);
					delete m_vecBullet[i];
					m_vecBullet.erase(m_vecBullet.begin() + i);
				}
				else
				{
					m_vecBullet[i]->Update(hero, scene);
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

	Point _pointBeginTop;
	Point _pointBeginBottom;

	if (this->getPositionX() > this->getBoundingBox().size.width)
	{
		_pointBeginTop = Point(this->getPositionX() - (this->getBoundingBox().size.width / 2),
			this->getPositionY() + (this->getBoundingBox().size.height / 2)
			);

		_pointBeginBottom = Point(this->getPositionX() - (this->getBoundingBox().size.width / 2),
			this->getPositionY() - (this->getBoundingBox().size.height / 2)
			);
	}
	else
	{
		return;
	}

	BotBulletGraphicComponent* _bulletTopPosition = new BotBulletGraphicComponent(_IDTopBullet, 120, CNT_NAME_BULLET_POSITION_TOP);
	_bulletTopPosition->ChangeState(BotBulletGraphicComponent::StateBullet::STATE_FIRE);

	_bulletTopPosition->setPosition(_pointBeginTop);
	_bulletTopPosition->setVisible(false);

	int _IDBottomBullet = rand() % 100000 + 0;
	BotBulletGraphicComponent* _bulletBottomPosition = new BotBulletGraphicComponent(_IDBottomBullet, 120, CNT_NAME_BULLET_POSITION_BOTTOM);
	_bulletBottomPosition->ChangeState(BotBulletGraphicComponent::StateBullet::STATE_FIRE);

	_bulletBottomPosition->setPosition(_pointBeginBottom);
	_bulletBottomPosition->setVisible(false);

	m_vecBullet.push_back(_bulletTopPosition);
	m_vecBullet.push_back(_bulletBottomPosition);

	m_stateAirplane = StateAirplane::STATE_MOVE;
}

void AirplaneEnemyGraphicComponent::SetStateCreateBullets(float dt)
{
	m_stateAirplane = StateAirplane::STATE_CREATE_BULLETS;
}

void AirplaneEnemyGraphicComponent::LoadValueProperties()
{
	int _orderAttackBottom	= 20;
	int _orderAttackTop		= 45;
	
	int _orderArmorBottom	= 50;
	int _orderArmorTop		= 90;
	
	int _orderHealthBottom	= 50;
	int _orderHealthTop		= 90;
	
	int _orderSpawnShotBottom	= 4;
	int _orderSpawnShotTop		= 10;
	
	int _randValue	= 0;
	
	for (int i = 0; i < CNT_QUENTITY_LEVELS; i++)
	{
		// fill value attack
		srand(time(NULL));
		_randValue = rand() % _orderAttackTop + _orderAttackBottom;
		m_vecAirplaneBlack[i].m_attack = _randValue;		
		_randValue = rand() % _orderAttackTop + _orderAttackBottom;
		m_vecAirplaneBlue[i].m_attack = _randValue;
		_randValue = rand() % _orderAttackTop + _orderAttackBottom;
		m_vecAirplaneGreen[i].m_attack = _randValue;
		_randValue = rand() % _orderAttackTop + _orderAttackBottom;
		m_vecAirplaneRed[i].m_attack = _randValue;

		_orderAttackBottom	+= 5;
		_orderAttackTop		+= 5;

		// fill value armor
		srand(time(NULL));
		_randValue = rand() % _orderArmorTop + _orderArmorBottom;
		m_vecAirplaneBlack[i].m_armor = _randValue;
		_randValue = rand() % _orderArmorTop + _orderArmorBottom;
		m_vecAirplaneBlue[i].m_armor = _randValue;
		_randValue = rand() % _orderArmorTop + _orderArmorBottom;
		m_vecAirplaneGreen[i].m_armor = _randValue;
		_randValue = rand() % _orderArmorTop + _orderArmorBottom;
		m_vecAirplaneRed[i].m_armor = _randValue;

		_orderArmorBottom	+= 5;
		_orderArmorTop		+= 5;

		// fill value health
		srand(time(NULL));
		_randValue = rand() % _orderHealthTop + _orderHealthBottom;
		m_vecAirplaneBlack[i].m_health = _randValue;
		_randValue = rand() % _orderHealthTop + _orderHealthBottom;
		m_vecAirplaneBlue[i].m_health = _randValue;
		_randValue = rand() % _orderHealthTop + _orderHealthBottom;
		m_vecAirplaneGreen[i].m_health = _randValue;
		_randValue = rand() % _orderHealthTop + _orderHealthBottom;
		m_vecAirplaneRed[i].m_health = _randValue;

		_orderHealthBottom  += 5;
		_orderHealthTop		+= 5;

		// fill value spawn shot
		srand(time(NULL));
		_randValue = rand() % _orderSpawnShotTop + _orderSpawnShotBottom;
		m_vecAirplaneBlack[i].m_spawnShot = _randValue;
		_randValue = rand() % _orderSpawnShotTop + _orderSpawnShotBottom;
		m_vecAirplaneBlue[i].m_spawnShot = _randValue;
		_randValue = rand() % _orderSpawnShotTop + _orderSpawnShotBottom;
		m_vecAirplaneGreen[i].m_spawnShot = _randValue;
		_randValue = rand() % _orderSpawnShotTop + _orderSpawnShotBottom;
		m_vecAirplaneRed[i].m_spawnShot = _randValue;

		if (_orderSpawnShotBottom)
		{
			--_orderSpawnShotBottom;
			_orderSpawnShotTop -= 2;
		}
	}
}

void AirplaneEnemyGraphicComponent::DetermineTypeObject()
{
	if (!GameScene::m_level)
	{
		LoadValueProperties();
	}

	std::string::size_type _findStr;

	if ((_findStr = m_typeObject.find("black")) != std::string::npos)
	{
		this->m_attack			= m_vecAirplaneBlack[GameScene::m_level].m_attack;
		this->m_armor			= m_vecAirplaneBlack[GameScene::m_level].m_armor;
		this->m_health			= m_vecAirplaneBlack[GameScene::m_level].m_health;;
		this->m_timeSpawnShot	= m_vecAirplaneBlack[GameScene::m_level].m_spawnShot;

	}
	else if ((_findStr = m_typeObject.find("blue")) != std::string::npos)
	{
		this->m_attack			= m_vecAirplaneBlue[GameScene::m_level].m_attack;
		this->m_armor			= m_vecAirplaneBlue[GameScene::m_level].m_armor;
		this->m_health			= m_vecAirplaneBlue[GameScene::m_level].m_health;;
		this->m_timeSpawnShot	= m_vecAirplaneBlue[GameScene::m_level].m_spawnShot;
	}
	else if ((_findStr = m_typeObject.find("green")) != std::string::npos)
	{
		this->m_attack			= m_vecAirplaneGreen[GameScene::m_level].m_attack;
		this->m_armor			= m_vecAirplaneGreen[GameScene::m_level].m_armor;
		this->m_health			= m_vecAirplaneGreen[GameScene::m_level].m_health;;
		this->m_timeSpawnShot	= m_vecAirplaneGreen[GameScene::m_level].m_spawnShot;
	}
	else if ((_findStr = m_typeObject.find("red")) != std::string::npos)
	{
		this->m_attack			= m_vecAirplaneRed[GameScene::m_level].m_attack;
		this->m_armor			= m_vecAirplaneRed[GameScene::m_level].m_armor;
		this->m_health			= m_vecAirplaneRed[GameScene::m_level].m_health;;
		this->m_timeSpawnShot	= m_vecAirplaneRed[GameScene::m_level].m_spawnShot;
	}

	if (m_typeObject == CNT_NAME_ENEMY_BLACK_1)
	{	
		SetPropertiesAirplane("res/Enemies/enemyBlack1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLACK_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlack5.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_BLUE_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyBlue5.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_GREEN_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyGreen5.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_1)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed1.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_2)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed2.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_3)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed3.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_4)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed4.png");
	}
	else if (m_typeObject == CNT_NAME_ENEMY_RED_5)
	{
		SetPropertiesAirplane("res/Enemies/enemyRed5.png");
	}
}

void AirplaneEnemyGraphicComponent::SetPropertiesAirplane(const std::string& i_filename)
{
	this->initWithFile(i_filename);
	this->setScale(m_visibleSize.width / this->getContentSize().width / 12,
		m_visibleSize.height / this->getContentSize().height / 10);
	this->setRotation(-90.0);
	this->setVisible(true);

	int _randTagForPhysicCollision = rand() % 100000 + 0;
		
	auto physicBodyEnemy = PhysicsBody::createBox(this->getContentSize());
	physicBodyEnemy->setContactTestBitmask(true);
	physicBodyEnemy->setDynamic(false);
	physicBodyEnemy->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	physicBodyEnemy->setTag(_randTagForPhysicCollision);
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

AirplaneEnemyGraphicComponent::~AirplaneEnemyGraphicComponent()
{
	CCLOG("destructor airplanes");
}

