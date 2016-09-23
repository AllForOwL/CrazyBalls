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
	enum StateHero
	{
		HERO_STATE_WALK,
		HERO_STATE_ATTACK,
		HERO_STATE_RUN,
		HERO_STATE_JUMP,
		HERO_STATE_FALL,
		HERO_STATE_WOUNDED,
		HERO_STATE_CHANGE_WEAPON_BULLET,
		HERO_STATE_DEATH
	};

	enum StateWeapon
	{
		WEAPON_STATE_FIRE,
		WEAPON_STATE_FIRE_UP,
		WEAPON_STATE_REST
	};

	enum StateBullet
	{
		BULLET_STATE_FIRE,
		BULLET_STATE_FIRE_UP,
		BULLET_STATE_REST
	};

	enum StatePhysic
	{
		PHYSIC_NOTHING,
		PHYSIC_KILL_ENEMY,
		PHYSIC_KILL_HERO
	};

	Monster::Monster(
						GraphicComponent* graphicComponentHero, GraphicComponent* graphiComponentWeapon, 
						GraphicComponent* graphicComponentBullet, GameObjectMonster* objectMonster, 
						InputComponent* inputComponent, InputComponent* botInputComponent,
						PhysicComponent* physicComponent
					 );

	virtual void Update(GameScene& scene);
	
	void ChangeWeapon(WeaponGraphicComponent& weapon);
	void ChangeBullet(PlayerBulletGraphicComponent& bullet);

	~Monster();

public:
	GraphicComponent*	m_graphicComponentHero;
	GraphicComponent*	m_graphicComponentHeroWeapon;
	GraphicComponent*	m_graphiComponentHeroBullet;
	GameObjectMonster*	m_objectMonster;
	InputComponent*		m_inputComponentHero;
	InputComponent*		m_botInputComponent;
	PhysicComponent*	m_physicComponent;
	StateHero			m_stateHero;
	StateWeapon			m_stateWeapon;
	StateBullet			m_stateBullet;
	StatePhysic			m_statePhysic;
	cocos2d::Label* m_lbl;

};

#endif