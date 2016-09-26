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
	LoadField();
}

void GameObjectMonster::Update(Monster& hero, GameScene& scene)
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
	m_enemy->setPosition(GetPosition());
	m_enemy->setName(_typeObjectEnemy);

	m_vecComponentEnemy.push_back(m_enemy);
	
	scene.addChild(m_vecComponentEnemy[m_vecComponentEnemy.size() - 1]);
}

void GameObjectMonster::LoadField()
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	// отримуємо другу половину поля
	int _widthField = _visibleSize.width / 2;
	
	std::vector<int> _vecPositionX;
	std::vector<int> _vecPositionY;

	/*int _end_X = _widthField + 50;
	do
	{
		_vecPositionX.push_back(_end_X);
		_end_X += 50;
	}
	while (_end_X < _visibleSize.width - 50);

	int _end_Y = 50;
	do
	{
		_vecPositionY.push_back(_end_Y);
		_end_Y += 50;
	} 
	while (_end_Y < _visibleSize.height - 50);
	*/

	_vecPositionX.push_back(260);
	_vecPositionX.push_back(310);
	_vecPositionX.push_back(360);

	_vecPositionY.push_back(50);
	_vecPositionY.push_back(100);
	_vecPositionY.push_back(150);
	_vecPositionY.push_back(200);
	_vecPositionY.push_back(250);

	for (int i = 0; i < _vecPositionX.size(); i++)
	{
		for (int j = 0; j < _vecPositionY.size(); j++)
		{
			m_vecField.push_back(Field(_vecPositionX[i], _vecPositionY[j], true));
		}
	}
}

cocos2d::Point GameObjectMonster::GetPosition()
{
	int _random_cols	= 0;
	int _random_rows	= 0;
	int _indexPosition	= 0;
	srand(time(NULL));
	do
	{
		_random_cols = rand() % CNT_COLS + 1;
		_random_rows = rand() % CNT_ROWS + 1;
		_indexPosition = _random_cols * _random_rows;
	}
	while (!FreePosition(_indexPosition));

	Point _position;
	_position.x = m_vecField[_indexPosition].m_X;
	_position.y = m_vecField[_indexPosition].m_Y;

	return _position;
}

bool GameObjectMonster::FreePosition(int indexPosition)
{
	if (indexPosition > CNT_MAX_INDEX_POSITION)
	{
		return false;
	}
	if (m_vecField[indexPosition].m_Free)
	{
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
			CCLOG("Release cell");
			break;
		}
	}
}

GameObjectMonster::~GameObjectMonster()
{
	
}
