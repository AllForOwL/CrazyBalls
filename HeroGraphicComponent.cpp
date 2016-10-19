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

HeroGraphicComponent::HeroGraphicComponent(const std::string& typeHero) : m_typeHero(typeHero)
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_fTopOrderScreen = 0.0f;
	m_fBottomOrderScreen = 0.0f;
	m_fPositionY = this->getPositionY();

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

	this->initWithFile("res/Hero/player/playerShip3_red.png");
	this->setRotation(90.0);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
	physicBodyHero->setContactTestBitmask(true);
	physicBodyHero->setCollisionBitmask(HERO_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyHero);
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	this->setTag(heroGraphicComponent.getTag());
	LoadNumberCoinsForTransitionNextLevel();

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

	this->initWithFile(m_vecSpritesFall[m_countSpriteInVectorFall]);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
//	physicBodyHero->setDynamic(false);
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
	m_vecSpritesDizzy.push_back("res/Hero/player/playerShip3_red.png");
	m_vecSpritesDizzy.push_back("res/Hero/player/playerShip3_red.png");
	m_vecSpritesDizzy.push_back("res/Hero/player/playerShip3_red.png");

	m_vecSpritesFall.push_back("res/Hero/player/playerShip3_red.png");
	m_vecSpritesFall.push_back("res/Hero/player/playerShip3_red.png");
	m_vecSpritesFall.push_back("res/Hero/player/playerShip3_red.png");
}

void HeroGraphicComponent::LoadNumberCoinsForTransitionNextLevel()
{
	m_vecNumberCoinsForTransitionNextLevel.push_back(50);
	int _numberCoins = 50;
	for (int i = 1; i < 12; i++)
	{
		_numberCoins = m_vecNumberCoinsForTransitionNextLevel[i-1] + 50;
		m_vecNumberCoinsForTransitionNextLevel.push_back(_numberCoins);
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

void HeroGraphicComponent::ChangeWeapon(Monster& i_hero, GameScene& i_scene)
{
	/*int _amountWeapon = i_hero.m_vecGraphicComponentWeapon.size();
	if (_amountWeapon == 0)
	{
		return;
	}

	if (_amountWeapon == 1)
	{
		i_hero.SetActiveWeapon(i_scene, 0);
		i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;

		return;
	}
	else
	{
		int _currentIndexWeapon = i_hero.GetIndexActiveWeapon();
		if (++_currentIndexWeapon >= _amountWeapon)
		{
			_currentIndexWeapon = 0;
		}
		i_hero.SetActiveWeapon(i_scene, _currentIndexWeapon);
	}
	i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;*/
}

void HeroGraphicComponent::ChangeBullet(Monster& i_hero, GameScene& i_scene)
{
	//int _amountBullet = i_hero.m_vecGraphicComponentBullet.size();
	//if (_amountBullet == 0)
	//{
	//	return;
	//}

	//if (_amountBullet == 1)
	//{
	//	i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;
	//	return;
	//}
	//else
	//{
	//	int _currentIndexBullet = i_hero.GetIndexActiveBullet();
	//	if (++_currentIndexBullet >= _amountBullet)
	//	{
	//		_currentIndexBullet = 0;
	//	}
	//	i_hero.SetActiveBullet(i_scene, _currentIndexBullet);
	//}
}

void HeroGraphicComponent::LoadSpritesDizzy(Monster& i_hero)
{
	if (++m_countSpriteInVectorDizzy == CNT_NUMBER_SPRITE_IN_DIZZY)
	{
		i_hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;
		m_countSpriteInVectorDizzy = 0;
		m_health -= 10;

		return;
	}
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesDizzy[m_countSpriteInVectorDizzy]));
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
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesFall[1]));
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
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesFall[0]));
}

void HeroGraphicComponent::GoToNextLevel(Monster& i_hero)
{
	/*int _coin = GetAttack();
	int _health = GetHealth();

	std::vector<int> _vecTagWeapon;
	int _tag = 0;
	for (int i = 0; i < i_hero.m_vecGraphicComponentWeapon.size(); i++)
	{
		_tag = i_hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->getTag();
		_vecTagWeapon.push_back(_tag);
	}

	auto reScene = TransitionFade::create(0.1f, TransitionMainScene::createScene(_coin, _health, _vecTagWeapon), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->replaceScene(reScene);*/
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
		case Monster::StateHero::HERO_STATE_WOUNDED:
		{
			LoadSpritesDizzy(hero);

			break;
		}
		case Monster::StateHero::HERO_STATE_CHANGE_WEAPON:
		{
			ChangeWeapon(hero, scene);

			break;
		}
		case Monster::StateHero::HERO_STATE_CHANGE_BULLET:
		{
			ChangeBullet(hero, scene);

			break;
		}
		case Monster::StateHero::HERO_STATE_DEATH:
		{
			this->removeFromParentAndCleanup(true);

			break;
		}
		case Monster::StateHero::HERO_STATE_WINNER:
		{
			GoToNextLevel(hero);			

			break;
		}
		case Monster::StateHero::HERO_STATE_TAKE_COIN:
		{
			ChangeCoins(CNT_COIN_DEFAULT);
			hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;

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