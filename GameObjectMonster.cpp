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
			if (m_vecComponentWeapon.size())
			{
				m_vecComponentWeapon[i]->Update(hero, scene);
			}
			if (m_vecComponentBullet.size())
			{
				m_vecComponentBullet[i]->Update(hero, scene);
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

		switch (_randomValue)
		{
			case 1:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_1;
				break;
			}
			case 2:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_2;
				break;
			}
			case 3:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_3;
				break;
			}
			case 4:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_4;
				break;
			}
			case 5:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_5;
				break;
			}
			case 6:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_6;
				break;
			}
			case 7:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_7;
				break;
			}
			case 8:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_8;
				break;
			}
			case 9:
			{
				_typeObjectEnemy = CNT_NAME_ENEMY_ROCK_9;
				break;
			}
				default:
				break;
		}
	
		int _attackEnemy	= 100; 
	//	int _attackbullet	= 200;
		int _health			= 100;

		//int _attackSumm = _attackEnemy + _attackbullet;

	//	m_stateBullet	= GameObjectMonster::StateBullet::STATE_NOTHING;

	//	std::str	ing _typeObjectEnemy	= CNT_NAME_ENEMY_ROCK_1;
		//std::string _typeObjectWeapon	= CNT_NAME_WEAPON_AK47;
		std::string _typeObjectBullet	= CNT_NAME_BULLET_DEFAULT;

		m_enemy		= new BreedGraphicComponent		(_attackEnemy, _health, _typeObjectEnemy);
		//m_bullet	= new BotBulletGraphicComponent	(, _typeObjectBullet);

		int _widthEnemy	 = m_enemy->getContentSize().width;
		int _heightEnemy = m_enemy->getContentSize().height;

		//int _widthBullet	= m_bullet->getContentSize().width;
		//int _heightBullet	= m_bullet->getContentSize().height;

		m_enemy->setScale(_visibleSize.width / _widthEnemy / 15,
							_visibleSize.height / _heightEnemy / 10);
		//m_bullet->setScale(_visibleSize.width / _widthBullet / 40,
		//					_visibleSize.height / _heightBullet / 40);

		int _randomValue_X = rand() % 350 + 250;
		int _randomValue_Y = rand() % 250 + 25;

		m_enemy->setPosition	(GetPosition());
//		m_bullet->setPosition	(_randomValue_X, _randomValue_Y);
	//	m_bullet->setVisible(false);

		m_enemy->setName	(_typeObjectEnemy);
		//m_bullet->setName	(_typeObjectBullet);

		m_vecComponentEnemy.push_back	(m_enemy);
		//m_vecComponentBullet.push_back	(m_bullet);

		scene.addChild(m_vecComponentEnemy[m_vecComponentEnemy.size() - 1]);
//		scene.addChild(m_vecComponentBullet[m_vecComponentBullet.size() - 1]);
}

void GameObjectMonster::LoadField()
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	int _x_begin = _visibleSize.width / 2;

	int _x_interval = _visibleSize.width / CNT_COLS;
	int _y_interval = _visibleSize.height / CNT_ROWS;

	std::vector<int> _vecPositionX;
	std::vector<int> _vecPositionY;

	_vecPositionX.push_back(_x_begin + _x_interval / 2);
	_vecPositionX.push_back(_vecPositionX[0] + _x_interval);
	_vecPositionX.push_back(_vecPositionX[1] + _x_interval);
	_vecPositionX.push_back(_vecPositionX[2] + _x_interval);
	_vecPositionX.push_back(_vecPositionX[3] + _x_interval);

	_vecPositionY.push_back(_y_interval / 2);
	_vecPositionY.push_back(_vecPositionY[0] + _y_interval);
	_vecPositionY.push_back(_vecPositionY[1] + _y_interval);
	_vecPositionY.push_back(_vecPositionY[2] + _y_interval);
	_vecPositionY.push_back(_vecPositionY[3] + _y_interval);
	_vecPositionY.push_back(_vecPositionY[4] + _y_interval);
	_vecPositionY.push_back(_vecPositionY[5] + _y_interval);

	for (int i = 0; i < CNT_COLS; i++)
	{
		for (int j = 0; j < CNT_ROWS; j++)
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
		_random_cols = rand() % CNT_COLS - 1 + 1;
		_random_rows = rand() % CNT_ROWS - 1 + 1;
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

GameObjectMonster::~GameObjectMonster()
{
	
}
