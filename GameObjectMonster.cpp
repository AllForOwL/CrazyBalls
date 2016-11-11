#include "GameObjectMonster.h"
#include "GameScene.h"
#include "BreedGraphicComponent.h"
#include "AirplaneEnemyGraphicComponent.h"
#include "WeaponGraphicComponent.h"
#include "BotBulletGraphicComponent.h"
#include "Monster.h"
#include "GraphicComponent.h"
#include "constants.h"
#include <time.h>      

const int CNT_COIN_FOR_ENEMY_BLACK	= 50;
const int CNT_COIN_FOR_ENEMY_BLUE	= 100;
const int CNT_COIN_FOR_ENEMY_GREEN	= 150;
const int CNT_COIN_FOR_ENEMY_RED	= 200;

std::string GameObjectMonster::to_string(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

GameObjectMonster::GameObjectMonster()
{
	m_sizeEnemy		= Point::ZERO;
	m_visibleSize	= Director::getInstance()->getVisibleSize();

	LoadNameEnemies();
}

GameObjectMonster::GameObjectMonster(GameObjectMonster& newObjectMonster)
{
	m_sizeEnemy		= Point::ZERO;
	m_visibleSize	= Director::getInstance()->getVisibleSize();
	
	LoadNameEnemies();
}

void GameObjectMonster::LoadNameEnemies()
{
	for (int i = 0; i < 9; i++)
	{
		m_vecNameEnemyMeteor.push_back("Rock" + to_string(i+1));
	}

	for (int i = 0; i < 5; i++)
	{
		m_vecNameEnemyAirplane.push_back("black_"	+ to_string(i + 1));
		m_vecNameEnemyAirplane.push_back("blue_"	+ to_string(i + 1));
		m_vecNameEnemyAirplane.push_back("green_"	+ to_string(i + 1));
		m_vecNameEnemyAirplane.push_back("red_"		+ to_string(i + 1));
	}
}

void GameObjectMonster::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateEnemy)
	{
		case Monster::StateEnemys::ENEMY_STATE_LIFE:
		{
			if (m_vecComponentEnemyMeteor.size())
			{
				for (int i = 0; i < m_vecComponentEnemyMeteor.size(); i++)
				{
					if (m_vecComponentEnemyMeteor.size())
					{
						m_vecComponentEnemyMeteor[i]->Update(hero, scene);
					}
				}
			}
			if (m_vecComponentEnemyAirplane.size())
			{
				for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
				{
					m_vecComponentEnemyAirplane[i]->Update(hero, scene);
					if (m_vecComponentEnemyAirplane[i]->m_vecBullet.size())
					{
						for (int j = 0; j < m_vecComponentEnemyAirplane[i]->m_vecBullet.size(); j++)
						{
							if (m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->getPositionX() < 0)
							{
								m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->removeFromParentAndCleanup(true);
								delete m_vecComponentEnemyAirplane[i]->m_vecBullet[j];
								m_vecComponentEnemyAirplane[i]->m_vecBullet.erase(m_vecComponentEnemyAirplane[i]->m_vecBullet.begin() + j);
							}
							else
							{
								m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->Update(hero, scene);
							}
						}
					}
				}
			}
			
			break;
		}
		case Monster::StateEnemys::ENEMY_STATE_DEATH:
		{
			for (int i = 0; i < m_vecComponentEnemyMeteor.size(); i++)
			{
				m_vecComponentEnemyMeteor[i]->removeFromParentAndCleanup(true);
			}
			for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
			{
				m_vecComponentEnemyAirplane[i]->removeAllChildrenWithCleanup(true);
			}
			break;
		}
	default:
		break;
	}
}

void GameObjectMonster::SpawnerEnemyMeteor(GameScene& scene)
{
	
}

void GameObjectMonster::SpawnerEnemyAirplane(GameScene& scene)
{
	srand(time(NULL));
	int _randTypeAirplane = rand() % m_vecNameEnemyAirplane.size() + 0;

	m_enemyAirplane = new AirplaneEnemyGraphicComponent(m_vecNameEnemyAirplane[_randTypeAirplane]);
	m_enemyAirplane->setPosition(GetPositionAirplane());

	m_vecComponentEnemyAirplane.push_back(m_enemyAirplane);
}

void GameObjectMonster::LoadField()
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	// отримуємо другу половину поля
	int _widthField = _visibleSize.width / 2;
	
	std::vector<int> _vecPositionX;
	std::vector<int> _vecPositionY;

	m_sizeEnemy = m_vecComponentEnemyMeteor[0]->getBoundingBox().size;

	int _tempPositionX = _widthField;
	while (_tempPositionX < _visibleSize.width)
	{
		_vecPositionX.push_back(_tempPositionX);
		_tempPositionX += m_sizeEnemy.width;
	}

	int _tempPositionY = m_sizeEnemy.height;
	while (_tempPositionY < _visibleSize.height)
	{
		_vecPositionY.push_back(_tempPositionY);
		_tempPositionY += m_sizeEnemy.height;
	}

	for (int i = 0; i < _vecPositionX.size(); i++)
	{
		for (int j = 0; j < _vecPositionY.size(); j++)
		{
			m_vecField.push_back(Field(_vecPositionX[i], _vecPositionY[j], true));
		}
	}
	for (int i = 0; i < m_vecField.size(); i++)
	{
		m_vecIndexFreePosition.push_back(i);
	}
}

cocos2d::Point GameObjectMonster::GetPosition()
{
	int _randPosition = 0;
	do
	{
		_randPosition = rand() % m_vecIndexFreePosition.size() + 0;
	}
	while (!FreePosition(_randPosition));

	Point _position;
	_position.x = m_vecField[_randPosition].m_X;
	_position.y = m_vecField[_randPosition].m_Y;

	return _position;
}

cocos2d::Point GameObjectMonster::GetPositionAirplane()
{
	int _randPositionX		= m_visibleSize.width - (m_enemyAirplane->getBoundingBox().size.width * 2);
	int _orderTopRand		= m_visibleSize.height - (m_enemyAirplane->getBoundingBox().size.height * 2);
	int _orderBottomRand	= m_enemyAirplane->getBoundingBox().size.height * 2;

	int _randPositionY = rand() % _orderTopRand + _orderBottomRand;
		
	return Point(_randPositionX, _randPositionY);
}

bool GameObjectMonster::FreePosition(int indexPosition)
{
	if (indexPosition > m_vecField.size())
	{
		return false;
	}
	if (m_vecField[indexPosition].m_Free)
	{
		m_vecIndexFreePosition.erase(m_vecIndexFreePosition.begin() + indexPosition);
		m_vecField[indexPosition].m_Free = false;
		return true;
	}
	else
	{
		return false;
	}	
}

void GameObjectMonster::ReleaseCell(Point point)
{
	for (int i = 0; i < m_vecField.size(); i++)
	{
		if (m_vecField[i].m_X == (int)point.x && m_vecField[i].m_Y == (int)point.y)
		{
			m_vecField[i].m_Free = true;
			m_vecIndexFreePosition.push_back(i);
			CCLOG("Release cell");
			break;
		}
	}
}

int GameObjectMonster::GetIndexEnemyForRemove(int tagEnemy) const
{
	int _tagEnemy = tagEnemy;
	for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
	{
		auto body = m_vecComponentEnemyAirplane[i]->getPhysicsBody();
		if (body->getTag() == _tagEnemy)
		{
			return i;
		}
	}
}

void GameObjectMonster::RemoveBullet(int tagEnemy)
{
	int _quentityAirplane	= 0;
	int _quentityBullet		= 0;
	int _tagEnemy = tagEnemy;
	for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
	{
		for (int j = 0; j < m_vecComponentEnemyAirplane[i]->m_vecBullet.size(); j++)
		{
			auto body = m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->getPhysicsBody();
			if (body->getTag() == _tagEnemy)
			{
				_quentityAirplane	= i;
				_quentityBullet		= j;
			}
		}
	}
	m_vecComponentEnemyAirplane[_quentityAirplane]->m_vecBullet[_quentityBullet]->removeFromParentAndCleanup(true);
	delete m_vecComponentEnemyAirplane[_quentityAirplane]->m_vecBullet[_quentityBullet];

	m_vecComponentEnemyAirplane[_quentityAirplane]->m_vecBullet.erase(m_vecComponentEnemyAirplane[_quentityAirplane]->m_vecBullet.begin() + _quentityBullet);
}

int GameObjectMonster::RemoveAndCleanEnemy(int indexEnemy)
{
	if (m_vecComponentEnemyAirplane.size())
	{
		int _indexEnemy				= indexEnemy;
		std::string _strTypeEnemy	= m_vecComponentEnemyAirplane[_indexEnemy]->GetTypeObject();

		for (int i = 0; i < m_vecComponentEnemyAirplane[_indexEnemy]->m_vecBullet.size(); i++)
		{
			m_vecComponentEnemyAirplane[_indexEnemy]->m_vecBullet[i]->removeFromParentAndCleanup(true);
		}

		m_vecComponentEnemyAirplane[_indexEnemy]->removeFromParentAndCleanup(true);
		delete m_vecComponentEnemyAirplane[_indexEnemy];

		m_vecComponentEnemyAirplane.erase(m_vecComponentEnemyAirplane.begin() + _indexEnemy);

		std::string::size_type _findStr;

		if ((_findStr = _strTypeEnemy.find("black")) != std::string::npos)
		{
			return CNT_COIN_FOR_ENEMY_BLACK;
		}
		else if ((_findStr = _strTypeEnemy.find("blue")) != std::string::npos)
		{
			return CNT_COIN_FOR_ENEMY_BLUE;
		}
		else if ((_findStr = _strTypeEnemy.find("green")) != std::string::npos)
		{
			return CNT_COIN_FOR_ENEMY_GREEN;
		}
		else if ((_findStr = _strTypeEnemy.find("red")) != std::string::npos)
		{
			return CNT_COIN_FOR_ENEMY_RED;
		}
	}
	else
	{
		return 0;
	}
}

int GameObjectMonster::GetParentBullet(int i_tagBullet) const
{
	for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
	{
		for (int j = 0; j < m_vecComponentEnemyAirplane[i]->m_vecBullet.size(); j++)
		{
			auto body = m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->getPhysicsBody();
			if (body->getTag() == i_tagBullet)
			{
				return i;
			}
		}
	}
}

int GameObjectMonster::GetCoinForEnemy(int i_tagBullet) const
{
	int _quentityAirplane = GetParentBullet(i_tagBullet);

	std::string _strTypeEnemy = m_vecComponentEnemyAirplane[_quentityAirplane]->GetTypeObject();
	std::string::size_type _findStr;

	if ((_findStr = _strTypeEnemy.find("black")) != std::string::npos)
	{
		return CNT_COIN_FOR_ENEMY_BLACK;
	}
	else if ((_findStr = _strTypeEnemy.find("blue")) != std::string::npos)
	{
		return CNT_COIN_FOR_ENEMY_BLUE;
	} 
	else if ((_findStr = _strTypeEnemy.find("green")) != std::string::npos)
	{
		return CNT_COIN_FOR_ENEMY_GREEN;
	}
	else if ((_findStr = _strTypeEnemy.find("red")) != std::string::npos)
	{
		return CNT_COIN_FOR_ENEMY_RED;
	}
}

int GameObjectMonster::GetDamage(int indexEnemy) const
{
	int _quentityAirplane = 0;
	for (int i = 0; i < m_vecComponentEnemyAirplane.size(); i++)
	{
		for (int j = 0; j < m_vecComponentEnemyAirplane[i]->m_vecBullet.size(); j++)
		{
			auto body = m_vecComponentEnemyAirplane[i]->m_vecBullet[j]->getPhysicsBody();
			if (body->getTag() == indexEnemy)
			{
				return m_vecComponentEnemyAirplane[i]->GetAttack();
			}
		}
	}
}

GameObjectMonster::~GameObjectMonster()
{
	CCLOG("destructor gameobject");
}
