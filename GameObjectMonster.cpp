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

		m_enemy->setScale(_visibleSize.width / _widthEnemy / 25,
							_visibleSize.height / _heightEnemy / 25);

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
