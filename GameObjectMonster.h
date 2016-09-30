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
		STATE_NOTHING
	};

	GameObjectMonster();

	void Update(Monster& hero, GameScene& scene);
	void Spawner(GameScene& scene);
	cocos2d::Point GetPosition();
	void LoadField();
	bool FreePosition(int indexPosition);
	void ReleaseCell(Point point);

	~GameObjectMonster();
public:
	std::vector<GraphicComponent*>	m_vecComponentEnemy;
	GraphicComponent*				m_enemy;

	std::vector<GraphicComponent*>	m_vecComponentWeapon;
	GraphicComponent*				m_weapon;

	std::vector<GraphicComponent*>	m_vecComponentBullet;
	GraphicComponent*				m_bullet;

	StateBullet			m_stateBullet;
	std::vector<Field>	m_vecField;
	std::vector<int>	m_vecIndexFreePosition;
};


// Add vector for bullet, weapon enemy

#endif