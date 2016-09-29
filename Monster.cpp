#include "Monster.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "WeaponGraphicComponent.h"
#include "GameObjectMonster.h"
#include "PhysicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "constants.h"

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

	ComponentHero* _tempWeapon = new ComponentHero(m_graphicComponentHeroWeapon, true);
	ComponentHero* _tempBullet = new ComponentHero(m_graphiComponentHeroBullet, true);

	m_vecGraphicComponentWeapon.push_back(_tempWeapon);
	m_vecGraphicComponentBullet.push_back(_tempBullet);
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

int Monster::GetIndexActiveWeapon()
{
	for (int i = 0; i < m_vecGraphicComponentWeapon.size(); i++)
	{
		if (m_vecGraphicComponentWeapon[i]->isActive())
		{
			return i;
		}
	}
}

int Monster::GetIndexActiveBullet()
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		if (m_vecGraphicComponentBullet[i]->isActive())
		{
			return i;
		}
	}
}

void Monster::AddWeapon(int typeWeapon)
{
	int _typeWeapon = typeWeapon;

	WeaponGraphicComponent* _weapon;

	switch (_typeWeapon)
	{
		case CNT_TYPE_OBJECT_WEAPON_AK47:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_AK47);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_GUN:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_GUN);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_MI71:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_MI71);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_MK15:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_MK15);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_REVOLVER_MONI_SHADE);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_STEN_GUN_SHADE_2);
			break;
		}
		case CNT_TYPE_OBJECT_WEAPON_TS23:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_TS23);
			break;											
		}
		case CNT_TYPE_OBJECT_WEAPON_UMG:
		{
			_weapon = new WeaponGraphicComponent(100, CNT_NAME_WEAPON_UMG);
			break;
		}
		default:
			break;
	}

	ComponentHero* _heroComponent = new ComponentHero(_weapon, false);
	m_vecGraphicComponentWeapon.push_back(_heroComponent);
}

void Monster::AddBullet(int typeBullet)
{
	int _typeBullet =  typeBullet;

	PlayerBulletGraphicComponent* _bulletComponent;
	
	if (_typeBullet == CNT_TYPE_OBJECT_BULLET_NORMAL)
	{
		_bulletComponent = new PlayerBulletGraphicComponent(20, CNT_NAME_BULLET_DEFAULT);
	}
	else if (_typeBullet == CNT_TYPE_OBJECT_BULLET_BOMB)
	{
		_bulletComponent = new PlayerBulletGraphicComponent(50, CNT_NAME_BOMB);
	}

	ComponentHero* _heroComponent = new ComponentHero(_bulletComponent, false);
	m_vecGraphicComponentBullet.push_back(_heroComponent);
}

void Monster::SetActiveBullet(int index)
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		m_vecGraphicComponentBullet[i]->SetNotActive();
	}

	this->m_vecGraphicComponentBullet[index]->SetActive();
}

void Monster::SetActiveWeapon(int index)
{
	for (int i = 0; i < m_vecGraphicComponentWeapon.size(); i++)
	{
		m_vecGraphicComponentWeapon[i]->SetNotActive();
	}

	this->m_vecGraphicComponentWeapon[index]->SetActive();
}

void Monster::Update(GameScene& scene)
{
	m_inputComponentHero->Update		(*this);
	m_graphicComponentHero->Update		(*this, scene);
	m_vecGraphicComponentWeapon[GetIndexActiveWeapon()]->m_GraphicComponent->Update(*this, scene);
	m_botInputComponent->Update			(*this);
	m_objectMonster->Update				(*this, scene);
	m_vecGraphicComponentBullet[GetIndexActiveBullet()]->m_GraphicComponent->Update(*this, scene);
	m_physicComponent->Update			(*this, scene);
}

Monster::~Monster()
{
	delete m_graphicComponentHero;
	delete m_graphicComponentHeroWeapon;
	delete m_inputComponentHero;
}

/*  GraphicComponent	- ����� ����� ������� 
	PhysicsComponent	- ����� �������� �����
	InputComponent		- ������ 䳿 � ���������
	Monster				- ��������� ��� ��� ����������
*/