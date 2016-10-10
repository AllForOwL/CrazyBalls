#include "HeroGraphicComponent.h"
#include "Monster.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "TransitionMainScene.h"


HeroGraphicComponent::HeroGraphicComponent(const std::string& typeHero) : m_typeHero(typeHero)
{
	this->setTag(0);
	LoadNumberCoinsForTransitionNextLevel();
	if (m_typeHero == CNT_NAME_HERO_HELL)
	{
		LoadSpritesForHell();
		m_attack = 120;
		m_health = 1000;
	}

	m_coins = 0;

	m_countSpriteInVectorWalk		= 0;
	m_countSpriteInVectorAttack		= 0;
	m_countSpriteInVectorRun		= 0;
	m_countSpriteInVectorDizzy		= 0;
	m_countSpriteInVectorDie		= 0;
	m_countSpriteInVectorFall		= 0;

	this->initWithFile(m_vecSpritesWalk[m_countSpriteInVectorWalk]);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
//	physicBodyHero->setDynamic(false);
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
		LoadSpritesForHell();
		m_attack = 120;
		m_health = 100;
	}

	m_coins = 0;

	m_countSpriteInVectorWalk = 0;
	m_countSpriteInVectorAttack = 0;
	m_countSpriteInVectorRun = 0;
	m_countSpriteInVectorDizzy = 0;
	m_countSpriteInVectorDie = 0;
	m_countSpriteInVectorFall = 0;

	this->initWithFile(m_vecSpritesWalk[m_countSpriteInVectorWalk]);

	auto physicBodyHero = PhysicsBody::createBox(this->getContentSize());
//	physicBodyHero->setDynamic(false);
	physicBodyHero->setContactTestBitmask(true);
	physicBodyHero->setCollisionBitmask(HERO_COLLISION_BITMASK);
	this->setPhysicsBody(physicBodyHero);
}

void HeroGraphicComponent::LoadSpritesForHell()
{
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0001.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0002.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0003.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0004.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0005.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0006.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0007.png");
	m_vecSpritesWalk.push_back("res/Hero/Walk/walk-0007.png");

	m_vecSpritesAttack.push_back("res/Hero/Attack/attack-0001.png");
	m_vecSpritesAttack.push_back("res/Hero/Attack/attack-0002.png");
	m_vecSpritesAttack.push_back("res/Hero/Attack/attack-0003.png");
	m_vecSpritesAttack.push_back("res/Hero/Attack/attack-0004.png");

	m_vecSpritesRun.push_back("res/Hero/Run/run-0001.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0002.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0003.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0004.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0005.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0006.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0007.png");
	m_vecSpritesRun.push_back("res/Hero/Run/run-0008.png");

	m_vecSpritesDie.push_back("res/Hero/Die/die-0001.png");
	m_vecSpritesDie.push_back("res/Hero/Die/die-0002.png");
	m_vecSpritesDie.push_back("res/Hero/Die/die-0003.png");
	m_vecSpritesDie.push_back("res/Hero/Die/die-0004.png");

	m_vecSpritesDizzy.push_back("res/Hero/Dizzy/dizzy-0001.png");
	m_vecSpritesDizzy.push_back("res/Hero/Dizzy/dizzy-0002.png");
	m_vecSpritesDizzy.push_back("res/Hero/Dizzy/dizzy-0003.png");

	m_vecSpritesFall.push_back("res/Hero/Fall/fall-0001.png");
	m_vecSpritesFall.push_back("res/Hero/Fall/fall-0002.png");
	m_vecSpritesFall.push_back("res/Hero/Fall/fall-0003.png");
}

void HeroGraphicComponent::LoadNumberCoinsForTransitionNextLevel()
{
	m_vecNumberCoinsForTransitionNextLevel.push_back(10);
	int _numberCoins = 50;
	for (int i = 1; i < 12; i++)
	{
		_numberCoins = m_vecNumberCoinsForTransitionNextLevel[i-1] + 50;
		m_vecNumberCoinsForTransitionNextLevel.push_back(_numberCoins);
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

/*virtual*/ void HeroGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	switch (hero.m_stateHero)
	{
		case Monster::StateHero::HERO_STATE_WALK:
		{
			if (++m_countSpriteInVectorWalk >= m_vecSpritesWalk.size())
			{
				m_countSpriteInVectorWalk = 0;
			}
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesWalk[m_countSpriteInVectorWalk]));
			break;
		}
		case Monster::StateHero::HERO_STATE_ATTACK:
		{
			if (++m_countSpriteInVectorAttack >= m_vecSpritesAttack.size())
			{
				m_countSpriteInVectorAttack = 0;
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
			}
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesAttack[m_countSpriteInVectorAttack]));
			break;
		}
		case Monster::StateHero::HERO_STATE_RUN:
		{
			if (++m_countSpriteInVectorRun >= m_vecSpritesRun.size())
			{
				m_countSpriteInVectorRun = 0;
			}
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesRun[m_countSpriteInVectorRun]));
			break;
		}
		case Monster::StateHero::HERO_STATE_JUMP:
		{
			Point _position = this->getPosition();
			_position.y += 5;
			this->setPosition(_position);
		
			Point _positionWeapon = hero.m_graphicComponentHeroWeapon->getPosition();
			_positionWeapon.y += 5;
			hero.m_graphicComponentHeroWeapon->setPosition(_positionWeapon);
			
			hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
			break;
		}
		case Monster::StateHero::HERO_STATE_FALL:
		{
			Point _position = this->getPosition();
			_position.y -= 5;
			this->setPosition(_position);

			Point _positionWeapon = hero.m_graphicComponentHeroWeapon->getPosition();
			_positionWeapon.y -= 5;
			hero.m_graphicComponentHeroWeapon->setPosition(_positionWeapon);

			hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;

			break;
		}
		case Monster::StateHero::HERO_STATE_WOUNDED:
		{
			if (++m_countSpriteInVectorDizzy == CNT_NUMBER_SPRITE_IN_DIZZY)
			{
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
				m_countSpriteInVectorDizzy = 0;
				m_health -= 10;
				break;
			}

			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesDizzy[m_countSpriteInVectorDizzy]));

			break;
		}
		case Monster::StateHero::HERO_STATE_CHANGE_WEAPON:
		{
			int _amountWeapon = hero.m_vecGraphicComponentWeapon.size();
			
			if (_amountWeapon == 0)
			{
				return;
			}

			if (_amountWeapon == 1)
			{
				hero.SetActiveWeapon(scene, 0);
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
				break;
			}
			else
			{
				int _currentIndexWeapon = hero.GetIndexActiveWeapon();

				if (++_currentIndexWeapon >= _amountWeapon)
				{
					_currentIndexWeapon = 0;
				}
				
				hero.SetActiveWeapon(scene, _currentIndexWeapon);
			}

			hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;

			break;
		}
		case Monster::StateHero::HERO_STATE_CHANGE_BULLET:
		{
			int _amountBullet = hero.m_vecGraphicComponentBullet.size();
			
			if (_amountBullet == 0)
			{
				return;
			}

			if (_amountBullet == 1)
			{
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
				break;
			}
			else
			{
				int _currentIndexBullet = hero.GetIndexActiveBullet();

				if (++_currentIndexBullet >= _amountBullet)
				{
					_currentIndexBullet = 0;
				}
				
				hero.SetActiveBullet(scene, _currentIndexBullet);
			}

			break;
		}
		case Monster::StateHero::HERO_STATE_DEATH:
		{
			this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_vecSpritesDie[m_countSpriteInVectorDie]));
		
			if (++m_countSpriteInVectorDie == m_vecSpritesDie.size())
			{
				hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
				this->removeFromParentAndCleanup(true);
			}
			break;
		}
		case Monster::StateHero::HERO_STATE_WINNER:
		{
			srand(time(NULL));
			int _coin	= hero.m_graphicComponentHero->GetAttack();
			int _health = hero.m_graphicComponentHero->GetHealth();
			std::vector<int> _vecTagWeapon;

			int _tag = 0;
			for (int i = 0; i < hero.m_vecGraphicComponentWeapon.size(); i++)
			{
				_tag = hero.m_vecGraphicComponentWeapon[i]->m_GraphicComponent->getTag();
				_vecTagWeapon.push_back(_tag);
			}

			auto reScene = TransitionFade::create(0.1f, TransitionMainScene::createScene(_coin, _health, _vecTagWeapon), Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
			Director::getInstance()->replaceScene(reScene);

			break;
		}
	}
}

/*virtual*/ int HeroGraphicComponent::GetAttack() const
{
	return m_attack;
}

/*virtual*/ void HeroGraphicComponent::SetTargetPointForBullet(cocos2d::Point point)
{

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

/*virtual*/ void HeroGraphicComponent::SetSpeedBullet(int speed)
{

}

/*virtual*/ int HeroGraphicComponent::GetSpeedBullet() const
{
	return 2;
}
 
/*virtual*/ void HeroGraphicComponent::DescreaseQuentityBullet()
{

}

/*virtual*/ int HeroGraphicComponent::GetQuentityBullet() const
{
	return 1;
}

HeroGraphicComponent::~HeroGraphicComponent()
{

}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	Monster				- контейнер для цих компонентів
*/