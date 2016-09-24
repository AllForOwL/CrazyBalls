#include "GameObjectMonster.h"
#include "GameScene.h"
#include "BreedGraphicComponent.h"
#include "WeaponGraphicComponent.h"
#include "BotBulletGraphicComponent.h"
#include "Monster.h"
#include "GraphicComponent.h"
#include "constants.h"
#include <time.h>       /* time */

GameObjectMonster::GameObjectMonster()
{

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
	//if (m_vecComponentEnemy.size() > 0)
	//{
	//	return;
	//}

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
		//m_enemy->_ID = 10;
		//m_bullet	= new BotBulletGraphicComponent	(, _typeObjectBullet);

		int _widthEnemy	 = m_enemy->getContentSize().width;
		int _heightEnemy = m_enemy->getContentSize().height;

		//int _widthBullet	= m_bullet->getContentSize().width;
		//int _heightBullet	= m_bullet->getContentSize().height;

		m_enemy->setScale(_visibleSize.width / _widthEnemy / 10,
							_visibleSize.height / _heightEnemy / 8);
		//m_bullet->setScale(_visibleSize.width / _widthBullet / 40,
		//					_visibleSize.height / _heightBullet / 40);

		int _randomValue_X = rand() % 350 + 250;
		int _randomValue_Y = rand() % 250 + 25;

		m_enemy->setPosition	(_randomValue_X, _randomValue_Y);
//		m_bullet->setPosition	(_randomValue_X, _randomValue_Y);
	//	m_bullet->setVisible(false);

		m_enemy->setName	(_typeObjectEnemy);
		//m_bullet->setName	(_typeObjectBullet);

		m_vecComponentEnemy.push_back	(m_enemy);
		//m_vecComponentBullet.push_back	(m_bullet);

		scene.addChild(m_vecComponentEnemy[m_vecComponentEnemy.size() - 1]);
//		scene.addChild(m_vecComponentBullet[m_vecComponentBullet.size() - 1]);
}

GameObjectMonster::~GameObjectMonster()
{
	
}