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

Monster::Monster(
				GraphicComponent& graphicComponentHero,			GraphicComponent& graphicComponentButtonFire,	
				GameObjectMonster& objectMonster,				InputComponent& inputComponent,					InputComponent& botInputComponent,
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
	m_stateBonus	= Monster::StateBonus::BONUS_WEAPON;

	m_counterID = 0;
}

void Monster::CreateBulletsForFire()
{
	if (m_vecGraphicComponentBullet.size())
	{
		return;
	}

	srand(time(NULL));
	int _IDTopBullet = m_counterID;

	PlayerBulletGraphicComponent* _bulletTopPosition = new PlayerBulletGraphicComponent(_IDTopBullet, 120, CNT_NAME_BULLET_POSITION_TOP);
	_bulletTopPosition->ChangeStateBullet(PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_FIRE);

	int _IDBottomBullet = ++m_counterID;
	++m_counterID;
	PlayerBulletGraphicComponent* _bulletBottomPosition = new PlayerBulletGraphicComponent(_IDBottomBullet, 120, CNT_NAME_BULLET_POSITION_BOTTOM);
	_bulletBottomPosition->ChangeStateBullet(PlayerBulletGraphicComponent::StateBullet::BULLET_STATE_FIRE);

	int _sizeMap = m_vecGraphicComponentBullet.size();

	m_vecGraphicComponentBullet.push_back(_bulletTopPosition);
	m_vecGraphicComponentBullet.push_back(_bulletBottomPosition);
}

void Monster::RemoveBullet(int i_tagBullet)
{
	for (int i = 0; i < m_vecGraphicComponentBullet.size(); i++)
	{
		auto body = m_vecGraphicComponentBullet[i]->getPhysicsBody();
		if (body->getTag() == i_tagBullet)
		{
			m_vecGraphicComponentBullet[i]->removeAllChildrenWithCleanup(true);
			m_vecGraphicComponentBullet[i]->getPhysicsBody()->removeFromWorld();

			m_vecGraphicComponentBullet.erase(m_vecGraphicComponentBullet.begin() + i);

			break;
			break;
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
		m_vecGraphicComponentBullet[i]->Update(*this, scene);
	}
}

void Monster::CheckHeroOnLevelCompete()
{
	if (m_graphicComponentHero->Winner())
	{
		m_stateHero = Monster::StateHero::HERO_STATE_WINNER;
	}
}

void Monster::CauseDamage(int damage)
{
	if (m_graphicComponentHero->Dead(damage))
	{
		m_stateHero		= Monster::StateHero::HERO_STATE_DEATH;
		m_stateWeapon	= Monster::StateWeapon::WEAPON_STATE_DEATH;
		m_stateEnemy	= Monster::StateEnemys::ENEMY_STATE_DEATH;
		m_stateBonus	= Monster::StateBonus::BONUS_DEATH;

		LoadGameOver();
	}
	else
	{
		m_stateHero = Monster::StateHero::HERO_STATE_WOUNDED;
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
	delete m_graphicComponentHero;
//	delete m_graphicComponentHeroWeapon;
	delete m_inputComponentHero;
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає дії з клавіатури
	Monster				- контейнер для цих компонентів
*/