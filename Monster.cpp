#include "Monster.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "WeaponGraphicComponent.h"
#include "GameObjectMonster.h"
#include "PhysicComponent.h"
#include "PlayerBulletGraphicComponent.h"

Monster::Monster(
				GraphicComponent* graphicComponentHero, GraphicComponent* graphicComponentWeapon,
				GraphicComponent* graphicComponentBullet, GameObjectMonster* objectMonster, 
				InputComponent* inputComponent, InputComponent* botInputComponent,
				PhysicComponent* physicComponent
				) 
							:	m_graphicComponentHero		(graphicComponentHero),
								m_graphicComponentHeroWeapon(graphicComponentWeapon),
								m_graphiComponentHeroBullet (graphicComponentBullet),
								m_objectMonster				(objectMonster),
								m_inputComponentHero		(inputComponent),
								m_botInputComponent			(botInputComponent),
								m_physicComponent			(physicComponent)
{
	m_stateHero		= Monster::StateHero::HERO_STATE_WALK;
	m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_REST;
	m_stateBullet	= Monster::StateBullet::BULLET_STATE_REST;
	m_statePhysic	= Monster::StatePhysic::PHYSIC_NOTHING;
}

void Monster::ChangeWeapon(WeaponGraphicComponent& weapon)
{
	m_graphicComponentHeroWeapon->removeFromParent();
	m_graphicComponentHeroWeapon = new WeaponGraphicComponent(weapon);
}

void Monster::ChangeBullet(PlayerBulletGraphicComponent& bullet)
{
	m_graphiComponentHeroBullet->removeFromParent();
	m_graphiComponentHeroBullet = new PlayerBulletGraphicComponent(bullet);
}

void Monster::Update(GameScene& scene)
{
	m_inputComponentHero->Update		(*this);
	m_graphicComponentHero->Update		(*this, scene);
	m_graphicComponentHeroWeapon->Update(*this, scene);
	m_botInputComponent->Update			(*this);
	m_objectMonster->Update				(*this, scene);
	m_graphiComponentHeroBullet->Update (*this, scene);
	m_physicComponent->Update			(*this, scene);
}

Monster::~Monster()
{
	delete m_graphicComponentHero;
	delete m_graphicComponentHeroWeapon;
	delete m_inputComponentHero;
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає дії з клавіатури
	Monster				- контейнер для цих компонентів
*/