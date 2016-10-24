#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class InputComponent;
class GraphicComponent;
class GameObjectMonster;
class PhysicComponent;
class WeaponGraphicComponent;
class PlayerBulletGraphicComponent;

class Monster
{
public:

	enum StateButtonFire
	{
		BUTTON_STATE_FIRE,
		BUTTON_STATE_RELEASE
	};

	enum StateHero
	{
		HERO_STATE_JUMP_UP,
		HERO_STATE_JUMP_DOWN,
		HERO_STATE_WOUNDED,
		HERO_STATE_CHANGE_BULLET,
		HERO_STATE_CHANGE_WEAPON,
		HERO_STATE_DEATH,
		HERO_STATE_WINNER,
		HERO_STATE_GO_TO_TARGET,
		HERO_STATE_TAKE_COIN,
		HERO_STATE_TAKE_POWER,
		HERO_STATE_TAKE_ARMOR,
		HERO_STATE_TAKE_BONUS_BULLET_QUENTITY
	};

	enum StateWeapon
	{
		WEAPON_STATE_FIRE,
		WEAPON_STATE_FIRE_UP,
		WEAPON_STATE_REST,
		WEAPON_CHECK_QUENTITY_BULLET,
		WEAPON_STATE_DEATH
	};

	enum StateEnemys
	{
		ENEMY_STATE_LIFE,
		ENEMY_STATE_DEATH
	};

	enum StatePhysic
	{
		PHYSIC_NOTHING,
		PHYSIC_KILL_ENEMY,
		PHYSIC_KILL_HERO
	};


	Monster(
			GraphicComponent& graphicComponentHero, 
			GraphicComponent& graphicComponentButtonFire,
			GameObjectMonster& objectMonster,
			InputComponent& inputComponent,
			InputComponent& botInputComponent,
			PhysicComponent& physicComponent
			);

	virtual void Update(GameScene& scene);
	
	void CheckQuentityBulletInActiveWeapon();
	void CheckHeroOnLevelCompete();
	void CauseDamage(int damage);
	void CauseBonus(int tagBonus);
	void LoadGameOver() const;
	void CreateBulletsForFire();
	void CreateBulletBonus();
	void RemoveBullet(int i_tagBullet);
	void ChangeBulletSpeed();

	~Monster();

public:
	GraphicComponent*	m_graphicComponentHero;
	GraphicComponent*	m_graphicComponentButtonFire;
	GameObjectMonster*	m_objectMonster;
	InputComponent*		m_inputComponentHero;
	InputComponent*		m_botInputComponent;
	PhysicComponent*	m_physicComponent;
	StateHero		m_stateHero;
	StateWeapon		m_stateWeapon;
	StatePhysic		m_statePhysic;
	StateEnemys		m_stateEnemy;
	StateButtonFire	m_stateButtonFire;

	std::vector<PlayerBulletGraphicComponent*> m_vecGraphicComponentBullet;
	
	int m_counterID;

	Size	m_visibleSize;

	bool	m_creatingBulletBonus;
};

#endif