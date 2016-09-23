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

	~GameObjectMonster();
public:
	std::vector<GraphicComponent*>	m_vecComponentEnemy;
	GraphicComponent*				m_enemy;

	std::vector<GraphicComponent*>	m_vecComponentWeapon;
	GraphicComponent*				m_weapon;

	std::vector<GraphicComponent*>	m_vecComponentBullet;
	GraphicComponent*				m_bullet;

	StateBullet		m_stateBullet;
};


// Add vector for bullet, weapon enemy

#endif