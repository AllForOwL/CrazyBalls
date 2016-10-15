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

struct ComponentHero
{
	GraphicComponent*	m_GraphicComponent;
	bool				m_active;
	int					m_quantity;

	ComponentHero(GraphicComponent* component, bool active) : m_GraphicComponent(component), m_active(active), m_quantity(1)
	{

	}
	void SetActive()
	{
		this->m_active = true;
	}

	void SetNotActive()
	{
		this->m_active = false;
	}

	bool isActive()
	{
		return m_active;
	}

	void IncreaseQuantityIdenticalType()
	{
		++m_quantity;
	}

	int GetQuentity() const
	{
		return m_quantity;
	}
};

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

	enum StateBonus
	{
		SUPER_BONUS,
		BONUS_WEAPON,
		BONUS_REST,
		BONUS_TAKE_BULLET,
		BONUS_TAKE_COIN,
		BONUS_TAKE_POWER,
		BONUS_TAKE_WEAPON,
		BONUS_DEATH
	};

	enum StatePhysic
	{
		PHYSIC_NOTHING,
		PHYSIC_KILL_ENEMY,
		PHYSIC_KILL_HERO
	};

	Monster(
				GraphicComponent& graphicComponentHero,			GraphicComponent& graphicComponentButtonFire,	GameObjectMonster& objectMonster, 
				InputComponent& inputComponent,					InputComponent& botInputComponent,
				PhysicComponent& physicComponent
			);

	virtual void Update(GameScene& scene);
	
	//virtual void SetTargetPointForBullet(cocos2d::Point point);

	void CheckQuentityBulletInActiveWeapon();

	void CheckHeroOnLevelCompete();

	void CauseDamage(int damage);

	void CauseBonus(int tagBonus);

	void LoadGameOver() const;

	void CreateBulletsForFire();

	~Monster();

public:
	GraphicComponent*	m_graphicComponentHero;
	GraphicComponent*	m_graphicComponentButtonFire;
	GameObjectMonster*	m_objectMonster;
	InputComponent*		m_inputComponentHero;
	InputComponent*		m_botInputComponent;
	PhysicComponent*	m_physicComponent;
	StateHero			m_stateHero;
	StateWeapon			m_stateWeapon;
	StatePhysic			m_statePhysic;
	StateEnemys			m_stateEnemy;
	StateBonus			m_stateBonus;
	StateButtonFire		m_stateButtonFire;

	std::vector<ComponentHero*> m_vecGraphicComponentBullet;
};

#endif