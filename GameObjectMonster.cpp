#include "GameObjectMonster.h"
#include "GameScene.h"
#include "BreedGraphicComponent.h"
#include "WeaponGraphicComponent.h"
#include "BotBulletGraphicComponent.h"
#include "Monster.h"
#include "GraphicComponent.h"
#include "constants.h"
#include <time.h>      

GameObjectMonster::GameObjectMonster()
{
	m_sizeEnemy = Point::ZERO;
}

void GameObjectMonster::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateEnemy)
	{
		case Monster::StateEnemys::ENEMY_STATE_LIFE:
		{
			if (m_vecComponentEnemy.size())
			{
				for (int i = 0; i < m_vecComponentEnemy.size(); i++)
				{
					if (m_vecComponentEnemy.size())
					{
						m_vecComponentEnemy[i]->Update(hero, scene);
					}
				}
			}
			break;
		}
		case Monster::StateEnemys::ENEMY_STATE_DEATH:
		{
			for (int i = 0; i < m_vecComponentEnemy.size(); i++)
			{
				m_vecComponentEnemy[i]->removeFromParentAndCleanup(true);
			}
			break;
		}
	default:
		break;
	}
}

void GameObjectMonster::Spawner(GameScene& scene)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	srand(time(NULL));
	int _randomValue = rand() % 9 + 1;
	
	std::string _typeObjectEnemy;
	int _attackEnemy	= 100;
	int _health			= 100;

	switch (_randomValue)
	{
		case 1:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_1;
			_attackEnemy		= 10;
			_health				= 15;
			break;
		}
		case 2:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_2;
			_attackEnemy		= 25;
			_health				= 10;
			break;
		}
		case 3:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_3;
			_attackEnemy		= 30;
			_health				= 20;
			break;
		}
		case 4:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_4;
			_attackEnemy		= 35;
			_health				= 20;
			break;
		}
		case 5:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_5;
			_attackEnemy		= 40;
			_health				= 20;
			break;
		}
		case 6:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_6;
			_attackEnemy		= 50;
			_health				= 45;
			break;
		}
		case 7:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_7;
			_attackEnemy		= 60;
			_health				= 40;
			break;
		}
		case 8:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_8;
			_attackEnemy		= 65;
			_health				= 50;
			break;
		}
		case 9:
		{
			_typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_9;
			_attackEnemy		= 25;
			_health				= 15;
			break;
		}
			default:
			break;
	}
	
	m_enemy	= new BreedGraphicComponent(_attackEnemy, _health, _typeObjectEnemy);
	
	int _widthEnemy	 = m_enemy->getContentSize().width;
	int _heightEnemy = m_enemy->getContentSize().height;

	m_enemy->setScale(_visibleSize.width / _widthEnemy / 20,
					 _visibleSize.height / _heightEnemy / 20);

	m_vecComponentEnemy.push_back(m_enemy);

	if (m_sizeEnemy.width == 0)
	{
		LoadField();
	}

	m_enemy->setPosition(GetPosition());
	m_enemy->setName(_typeObjectEnemy);

	
	scene.addChild(m_vecComponentEnemy[m_vecComponentEnemy.size() - 1]);
}

void GameObjectMonster::LoadField()
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	// отримуємо другу половину поля
	int _widthField = _visibleSize.width / 2;
	
	std::vector<int> _vecPositionX;
	std::vector<int> _vecPositionY;

	m_sizeEnemy = m_vecComponentEnemy[0]->getBoundingBox().size;

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

	for (int i = 0; i < m_vecComponentEnemy.size(); i++)
	{
		auto body = m_vecComponentEnemy[i]->getPhysicsBody();
		if (body->getTag() == _tagEnemy)
		{
			return i;
		}
	}
}

int GameObjectMonster::RemoveAndCleanEnemy(int indexEnemy)
{
	if (m_vecComponentEnemy.size())
	{
		int _indexEnemy = indexEnemy;
		int _coinEnemy = m_vecComponentEnemy[_indexEnemy]->GetValue();

		ReleaseCell(m_vecComponentEnemy[_indexEnemy]->getPosition());
		m_vecComponentEnemy[_indexEnemy]->removeFromParentAndCleanup(true);
		m_vecComponentEnemy.erase(m_vecComponentEnemy.begin() + _indexEnemy);

		return _coinEnemy;
	}
	else
	{
		return 0;
	}
}

int GameObjectMonster::GetCoinForEnemy() const
{
	return m_coinForEnemy;
}

int GameObjectMonster::GetDamage(int indexEnemy) const
{
	return m_vecComponentEnemy[indexEnemy]->GetAttack();
}

GameObjectMonster::~GameObjectMonster()
{
	
}
