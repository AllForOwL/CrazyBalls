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
				GraphicComponent* graphicComponentHero,		GraphicComponent* graphicComponentWeapon,
				GraphicComponent* graphicComponentBullet,	GameObjectMonster* objectMonster, 
				InputComponent* inputComponent,				InputComponent* botInputComponent,
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
	m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_FIRE;
	m_stateBullet	= Monster::StateBullet::BULLET_STATE_REST;
	m_statePhysic	= Monster::StatePhysic::PHYSIC_NOTHING;
	m_stateEnemy	= Monster::StateEnemys::ENEMY_STATE_LIFE;;
	m_stateBonus	= Monster::StateBonus::BONUS_WEAPON;

	ComponentHero* _tempWeapon = new ComponentHero(m_graphicComponentHeroWeapon, true);
	ComponentHero* _tempBullet = new ComponentHero(m_graphiComponentHeroBullet, true);

	m_vecGraphicComponentWeapon.push_back(_tempWeapon);
	m_vecGraphicComponentBullet.push_back(_tempBullet);
}

int Monster::GetIndexActiveWeapon()
{
	if (!m_vecGraphicComponentWeapon.size())
	{
		return -1;
	}

	for (int i = 0; i < m_vecGraphicComponentWeapon.size(); i++)
	{
		if (m_vecGraphicComponentWeapon[i]->isActive())
		{
			return i;
		}
	}

	m_vecGraphicComponentWeapon[GetRandWeapon()]->SetActive();

	return GetRandWeapon();
}

int Monster::GetRandWeapon()
{
	int _quentityWeapon = m_vecGraphicComponentWeapon.size();
	--_quentityWeapon;

	if (_quentityWeapon == 0)
	{
		return 0;
	}
	else
	{
		return  rand() % _quentityWeapon + 0;
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

	bool _findParallel = false;
	for (int i = 0; i < m_vecGraphicComponentWeapon.size(); i++)
	{
		if (m_vecGraphicComponentWeapon[i]->m_GraphicComponent->GetTypeObject() == _weapon->GetTypeObject())
		{
			m_vecGraphicComponentWeapon[i]->IncreaseQuantityIdenticalType();
			_findParallel = true;
			break;
			break;
		}
	}
	
	if (!_findParallel)
	{
		ComponentHero* _heroComponent = new ComponentHero(_weapon, false);
		m_vecGraphicComponentWeapon.push_back(_heroComponent);
	}
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

void Monster::SetActiveBullet(GameScene& scene, int index)
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		m_vecGraphicComponentBullet[i]->SetNotActive();
		if (!m_vecGraphicComponentBullet[i]->m_GraphicComponent->getParent())
		{
			scene.removeChildByName(m_vecGraphicComponentBullet[i]->m_GraphicComponent->getName());
		}
	}

	this->m_vecGraphicComponentBullet[index]->SetActive();
	scene.addChild(m_vecGraphicComponentBullet[index]->m_GraphicComponent);
}

void Monster::SetActiveWeapon(GameScene& scene, int index)
{
	for (int i = 0; i < m_vecGraphicComponentWeapon.size(); i++)
	{
		m_vecGraphicComponentWeapon[i]->SetNotActive();
		m_vecGraphicComponentWeapon[i]->m_GraphicComponent->setPosition(Point(-10, -10));
		m_vecGraphicComponentWeapon[i]->m_GraphicComponent->setVisible(false);
	}

	this->m_vecGraphicComponentWeapon[index]->SetActive();
	if (!m_vecGraphicComponentWeapon[index]->m_GraphicComponent->getParent())
	{
		scene.addChild(m_vecGraphicComponentWeapon[index]->m_GraphicComponent);
		m_vecGraphicComponentWeapon[index]->m_GraphicComponent->setVisible(true);
		m_vecGraphicComponentWeapon[index]->m_GraphicComponent->setPosition(m_graphicComponentHero->getPosition().x, m_graphicComponentHero->getPosition().y - 18);
	}
	else
	{
		m_vecGraphicComponentWeapon[index]->m_GraphicComponent->setVisible(true);
	}
}

void Monster::Update(GameScene& scene)
{
	m_inputComponentHero->Update		(*this);
	m_graphicComponentHero->Update		(*this, scene);
	m_botInputComponent->Update			(*this);
	m_objectMonster->Update				(*this, scene);
	m_physicComponent->Update			(*this, scene);
	
	int _indexActiveWeapon = GetIndexActiveWeapon();
	int _indexActiveBullet = GetIndexActiveBullet();
	if (_indexActiveWeapon != -1)
	{
		if (!m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->getParent() || 
			!m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->isVisible()
		   )
		{
			SetActiveWeapon(scene, _indexActiveWeapon);
		}
		m_vecGraphicComponentWeapon[_indexActiveWeapon]->m_GraphicComponent->Update(*this, scene);
		m_vecGraphicComponentBullet[_indexActiveBullet]->m_GraphicComponent->Update(*this, scene);
	}
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