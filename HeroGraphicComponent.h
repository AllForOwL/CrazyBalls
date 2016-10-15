#ifndef __HERO_GRAPHIC_COMPONENT_H__
#define __HERO_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class HeroGraphicComponent : public GraphicComponent
{
public:
	HeroGraphicComponent(const std::string& typeHero);
	HeroGraphicComponent(HeroGraphicComponent& heroGraphiComponent);
	
	virtual void Update(Monster& hero, GameScene& scene);
	
	virtual int GetValue() const;
	virtual bool Winner() const;
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);
	virtual void ChangeCoins(int coins);
	virtual void ChangeHealth(int health);

	virtual void SetTargetPosition_YForHero(int target_y);

	void LoadNameSpritesForHell();
	void LoadNumberCoinsForTransitionNextLevel();

	void SpeedHeroSuitablyEnemy(Monster& i_hero);
	
	void ChangeWeapon(Monster& i_hero, GameScene& i_scene);
	void ChangeBullet(Monster& i_hero, GameScene& i_scene);
	
	void LoadSpritesDizzy(Monster& i_hero);

	void JumpUp(Monster& i_hero);
	void JumpDown(Monster& i_hero);
	void GoToNextLevel(Monster& i_hero);

	virtual int GetArmor() const;

	~HeroGraphicComponent();

public:
	std::vector<std::string> m_vecSpritesFall;
	std::vector<std::string> m_vecSpritesDizzy;

	std::vector<int> m_vecNumberCoinsForTransitionNextLevel;

	int m_countSpriteInVectorDizzy;
	int m_countSpriteInVectorFall;

	std::string m_typeHero;

	int m_attack;
	int m_health;
	int m_coins;
	int m_armor;

	int m_target_Y;
	int m_speed;

	int m_speed_Y;
	int m_sizeEnemy;
	bool m_getSizeEnemy;

	// refactoring

	Size  m_visibleSize;
	float m_fTopOrderScreen;
	float m_fBottomOrderScreen;
	float m_fPositionY;
};

#endif