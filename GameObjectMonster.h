#ifndef __GAME_OBJECT_MONSTER_H__
#define __GAME_OBJECT_MONSTER_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameScene;
class BreedGraphicComponent;
class Monster;
class GraphicComponent;

// interface for other graphics classes
class GameObjectMonster
{
public:

	struct Field
	{
		int		m_X;
		int		m_Y;
		bool	m_Free;

		Field(int x, int y, bool state) : m_X(x), m_Y(y), m_Free(state)
		{

		}
	};
	
	enum StateBullet
	{
		STATE_FIRE,
		STATE_FIRE_UP,
		STATE_FIRE_BOMB,
		STATE_HIT_IN_TARGET,
		STATE_REMOVE_ENEMY,
		STATE_NOTHING
	};

	GameObjectMonster();

	void Update					(Monster& hero, GameScene& scene);
	void SpawnerEnemyMeteor		(GameScene& scene);
	void SpawnerEnemyAirplane	(GameScene& scene);
	cocos2d::Point GetPosition();
	void LoadField();
	bool FreePosition			(int indexPosition);
	void ReleaseCell			(Point point);

	int GetIndexEnemyForRemove	(int tagEnemy) const;
	int RemoveAndCleanEnemy		(int tagEnemy);
	int GetCoinForEnemy() const;
	int GetDamage				(int indexEnemy) const;

	void LoadNameEnemies();

	~GameObjectMonster();
public:
	std::vector<GraphicComponent*>	m_vecComponentEnemyMeteor;
	GraphicComponent*				m_enemyMeteor;

	std::vector<GraphicComponent*>	m_vecComponentEnemyAirplane;
	GraphicComponent*				m_enemyAirplane;

	std::vector<GraphicComponent*>	m_vecComponentWeapon;
	GraphicComponent*				m_weapon;

	std::vector<GraphicComponent*>	m_vecComponentBullet;
	GraphicComponent*				m_bullet;

	std::vector<std::string> m_vecNameEnemyMeteor;
	std::vector<std::string> m_vecNameEnemyAirplane;

	StateBullet			m_stateBullet;
	std::vector<Field>	m_vecField;
	std::vector<int>	m_vecIndexFreePosition;
	cocos2d::Size		m_sizeEnemy;

	int					m_coinForEnemy;
};


// Add vector for bullet, weapon enemy

#endif