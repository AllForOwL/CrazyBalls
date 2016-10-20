#include "HeroGraphicComponent.h"
#include "Monster.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "TransitionMainScene.h"

const int CNT_SPEED_HERO				= 5;
const int CNT_VISIBLE_ZONE_ENEMY		= 3;
const int CNT_COUNT_SPRITES_IN_VECTOR	= 3;

const int CNT_COIN_DEFAULT	= 50;
const int CNT_POWER_DEFAULT = 20;

std::vector<int> HeroGraphicComponent::m_vecNumberCoinsForTransitionNextLevel(CNT_QUENTITY_LEVELS);

HeroGraphicComponent::HeroGraphicComponent(const std::string& typeHero) : m_typeHero(typeHero)
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_fTopOrderScreen = 0.0f;
	m_fBottomOrderScreen = 0.0f;
	m_fPositionY = this->getPositionY();

	if (!m_vecNumberCoinsForTransitionNextLevel.size())
	{
		LoadNumberCoinsForTransitionNextLevel();
	}

	this->m_getSizeEnemy = false;
	this->m_speed_Y = 5;
	this->m_sizeEnemy = 0;
	this->m_target_Y = 0;
	this->m_speed    = CNT_SPEED_HERO;
	this->setTag(0);
	
	LoadNumberCoinsForTransitionNextLevel();
	
	if (m_typeHero == CNT_NAME_HERO_HELL)
	{
		LoadNameSpritesForHell();
		m_attack = 120;
		m_health = 1000;
		m_coins = 0;
		m_armor = 100;
	}

	m_countSpriteInVectorDizzy		= 0;
	m_countSpriteInVectorFall		= 0;

	this->initWithFile(m_filename);
	this->setRotation(90.0);

	this->setPosition(m_visibleSize.width / this->getContentSize().width + 100,
		m_visibleSize.height / this->getContentSize().height + 100);
	this->setScale(m_visibleSize.width / this->getContentSize().width / 10,
		m_visibleSize.height / this->getContentSize().height / 8);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
	physicBodyHero->setContactTestBitmask(true);
	physicBodyHero->setDynamic(false); 
	physicBodyHero->setCollisionBitmask(HERO_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyHero);
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	this->setTag(heroGraphicComponent.getTag());
	
	if (!m_vecNumberCoinsForTransitionNextLevel.size())
	{
		LoadNumberCoinsForTransitionNextLevel();
	}

	if (m_typeHero == CNT_NAME_HERO_HELL)
	{
		LoadNameSpritesForHell();
		m_attack = 120;
		m_health = 100;
	}

	m_coins = 0;
	m_speed = CNT_SPEED_HERO;

	m_countSpriteInVectorDizzy	= 0;
	m_countSpriteInVectorFall	= 0;

	this->initWithFile(m_filename);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
	physicBodyHero->setDynamic(false);
	physicBodyHero->setContactTestBitmask(true);
	physicBodyHero->setCollisionBitmask(HERO_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyHero);
}

int HeroGraphicComponent::GetArmor() const
{
	return m_armor;
}

void HeroGraphicComponent::LoadNameSpritesForHell()
{
	m_filename = "res/Hero/player/playerShip1_orange.png";
}

void HeroGraphicComponent::LoadNumberCoinsForTransitionNextLevel()
{
	int _numberCoins = 500;
	m_vecNumberCoinsForTransitionNextLevel[0] = _numberCoins;
	for (int i = 1; i < CNT_QUENTITY_LEVELS; i++)
	{
		m_vecNumberCoinsForTransitionNextLevel[i] = m_vecNumberCoinsForTransitionNextLevel[i-1] + _numberCoins;
	}	
}

void HeroGraphicComponent::SpeedHeroSuitablyEnemy(Monster& i_hero)
{
	if (i_hero.m_objectMonster->m_vecComponentEnemyMeteor.size())
	{
		m_getSizeEnemy = true;
		m_speed_Y = i_hero.m_objectMonster->m_vecComponentEnemyMeteor[0]->getBoundingBox().size.height / 2;
	}
}

/*virtual*/ bool HeroGraphicComponent::Dead(int wounded)
{
	m_health -= wounded;

	if (m_health < 0)
	{
		this->removeFromParentAndCleanup(true);
		return true;
	}
	else
	{
		return false;
	}
}

void HeroGraphicComponent::JumpUp(Monster& i_hero)
{
	m_fPositionY = this->getPositionY();
	m_fTopOrderScreen = (m_visibleSize.height - (this->getBoundingBox().size.height / 2));

	if (m_fPositionY >= m_fTopOrderScreen)
	{
		i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_DOWN;
		return;
	}
	else
	{
		m_fPositionY += m_speed_Y;
	}

	this->setPositionY(m_fPositionY);
}

void HeroGraphicComponent::JumpDown(Monster& i_hero)
{
	m_fPositionY = this->getPositionY();

	if (m_fPositionY <= m_fBottomOrderScreen)
	{
		i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;
		return;
	}
	else
	{
		m_fPositionY -= m_speed_Y;
	}

	this->setPositionY(m_fPositionY);
}

/*virtual*/ void HeroGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (!this->getParent())
	{
		scene.addChild(this);
	}

	if (!m_getSizeEnemy)
	{
		SpeedHeroSuitablyEnemy(hero);
	}

	switch (hero.m_stateHero)
	{
		case Monster::StateHero::HERO_STATE_JUMP_UP:
		{
			JumpUp(hero);
			
			break;
		}
		case Monster::StateHero::HERO_STATE_JUMP_DOWN:
		{
			if (m_fBottomOrderScreen)
			{
				JumpDown(hero);
			}
			else
			{
				m_fBottomOrderScreen = scene.m_gameLayer->m_menuBarBottom->getBoundingBox().size.height;
				m_fBottomOrderScreen += this->getBoundingBox().size.height / 2;
				JumpDown(hero);
			}

			break;
		}
		case Monster::StateHero::HERO_STATE_DEATH:
		{
			this->removeFromParentAndCleanup(true);

			break;
		}
		case Monster::StateHero::HERO_STATE_WINNER:
		{
			OpenNextLevel();

			break;
		}
		case Monster::StateHero::HERO_STATE_TAKE_COIN:
		{
			ChangeCoins(CNT_COIN_DEFAULT);
		
			break;
		}
		case Monster::StateHero::HERO_STATE_TAKE_POWER:
		{
			ChangeHealth(CNT_POWER_DEFAULT);
			hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_DOWN;

			break;
		}
	}
}

void HeroGraphicComponent::OpenNextLevel()
{
	srand(time(NULL));
	auto reScene = TransitionFade::create(0.5f, GameScene::createScene(true, m_coins, m_health), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);
}

/*virtual*/ int HeroGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ void HeroGraphicComponent::SetTargetPosition_YForHero(int target_y)
{
	this->m_target_Y = target_y;
}

/*virtual*/ int HeroGraphicComponent::GetHealth() const
{
	return m_health;
}

/*virtual*/ std::string HeroGraphicComponent::GetTypeObject() const
{
	return m_typeHero;
}

/*virtual*/ void HeroGraphicComponent::ChangeCoins(int coins)
{
	m_coins += coins;

	if (this->Winner())
	{
		OpenNextLevel();
	}
}

/*virtual*/ void HeroGraphicComponent::ChangeHealth(int health)
{
	m_health += health;
}

/*virtual*/ bool HeroGraphicComponent::Winner() const
{
	if (m_coins >= m_vecNumberCoinsForTransitionNextLevel[GameScene::m_level])
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*virtual*/ int HeroGraphicComponent::GetValue() const
{
	return m_coins;
}

HeroGraphicComponent::~HeroGraphicComponent()
{
	CCLOG("destructor herographic");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	Monster				- контейнер для цих компонентів
*/