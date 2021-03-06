#include "Monster.h"
#include "InputComponent.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "WeaponGraphicComponent.h"
#include "GameObjectMonster.h"
#include "PhysicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "GameOverScene.h"
#include "constants.h"
#include "PlayerBulletGraphicComponent.h"
#include <memory>


Monster::Monster(
					GraphicComponent& graphicComponentHero,  
					GraphicComponent& graphicComponentButtonFire,
					GameObjectMonster& objectMonster,
					InputComponent& inputComponent,
					InputComponent& botInputComponent,
					PhysicComponent& physicComponent
				) 
							:	m_graphicComponentHero		(&graphicComponentHero),
								m_graphicComponentButtonFire(&graphicComponentButtonFire),
								m_objectMonster				(&objectMonster),
								m_inputComponentHero		(&inputComponent),
								m_botInputComponent			(&botInputComponent),
								m_physicComponent			(&physicComponent)
{
	m_stateHero		= Monster::StateHero::HERO_STATE_JUMP_UP;
	m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_FIRE;
	m_statePhysic	= Monster::StatePhysic::PHYSIC_NOTHING;
	m_stateEnemy	= Monster::StateEnemys::ENEMY_STATE_LIFE;;

	m_creatingBulletBonus = false;
	m_counterID = 0;
	m_visibleSize = Director::getInstance()->getVisibleSize();
}

void Monster::CreateBulletsForFire()
{
	if (m_vecGraphicComponentBullet.size())
	{
		return;
	}

	++m_counterID;
	PlayerBulletGraphicComponent* _bulletTopPosition = new PlayerBulletGraphicComponent(m_counterID, 120, CNT_NAME_BULLET_POSITION_TOP);
	_bulletTopPosition->ChangeStateBullet(PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_FIRE);

	++m_counterID;
	PlayerBulletGraphicComponent* _bulletBottomPosition = new PlayerBulletGraphicComponent(m_counterID, 120, CNT_NAME_BULLET_POSITION_BOTTOM);
	_bulletBottomPosition->ChangeStateBullet(PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_FIRE);

	if (m_creatingBulletBonus)
	{
		++m_counterID;
		PlayerBulletGraphicComponent* _bulletBonus = new PlayerBulletGraphicComponent(m_counterID, 120, CNT_NAME_BULLET_BONUS);
		_bulletBonus->ChangeStateBullet(PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_FIRE);

		m_vecGraphicComponentBullet.push_back(_bulletBonus);
	}

	m_vecGraphicComponentBullet.push_back(_bulletTopPosition);
	m_vecGraphicComponentBullet.push_back(_bulletBottomPosition);
}

void Monster::CreateBulletBonus()
{
	if (!m_creatingBulletBonus)
	{
		m_creatingBulletBonus = true;
	}
}

void Monster::ChangeBulletSpeed()
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		m_vecGraphicComponentBullet[i]->m_stateBullet = PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_BONUS_SPEED;
	}
}

void Monster::RemoveBullet(int i_tagBullet)
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		auto body = m_vecGraphicComponentBullet[i]->getPhysicsBody();
		if (body->getTag() == i_tagBullet)
		{
			m_vecGraphicComponentBullet[i]->removeFromParentAndCleanup(true);
			delete m_vecGraphicComponentBullet[i];

			m_vecGraphicComponentBullet.erase(m_vecGraphicComponentBullet.begin() + i);

			return;
		}
	}
}

void Monster::Update(GameScene& scene)
{
	m_inputComponentHero->Update		(*this);
	m_graphicComponentHero->Update		(*this, scene);
	m_graphicComponentButtonFire->Update(*this, scene);
	m_botInputComponent->Update			(*this);
	m_objectMonster->Update				(*this, scene);
	m_physicComponent->Update			(*this, scene);

	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		if (m_vecGraphicComponentBullet[i]->getPositionX() > m_visibleSize.width)
		{
			m_vecGraphicComponentBullet[i]->removeFromParentAndCleanup(true);
			delete m_vecGraphicComponentBullet[i];

			m_vecGraphicComponentBullet.erase(m_vecGraphicComponentBullet.begin() + i);
		}
		else
		{
			m_vecGraphicComponentBullet[i]->Update(*this, scene);
		}
	}
}

void Monster::CauseDamage(int damage)
{
	if (m_graphicComponentHero->Dead(damage))
	{
		m_stateHero		= Monster::StateHero::HERO_STATE_DEATH;
		m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_DEATH;
		m_stateEnemy	= Monster::StateEnemys::ENEMY_STATE_DEATH;

		LoadGameOver();
	}
}

void Monster::LoadGameOver() const
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(1.0f, GameOverScene::createScene(), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}

Monster::~Monster()
{
	CCLOG("destructor monster");
}

/*  GraphicComponent	- ����� ����� ������� 
	PhysicsComponent	- ����� �������� �����
	InputComponent		- ������ 䳿 � ���������
	Monster				- ��������� ��� ��� ����������
*/