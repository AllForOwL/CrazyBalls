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

	virtual void SetSpeedBullet(int speed);
	virtual int GetSpeedBullet() const;

	virtual void DescreaseQuentityBullet();
	virtual int  GetQuentityBullet() const;

	void LoadSpritesForHell();
	void LoadNumberCoinsForTransitionNextLevel();

	~HeroGraphicComponent();

public:
	std::vector<std::string> m_vecSpritesWalk;
	std::vector<std::string> m_vecSpritesAttack;
	std::vector<std::string> m_vecSpritesRun;
	std::vector<std::string> m_vecSpritesFall;
	std::vector<std::string> m_vecSpritesDie;
	std::vector<std::string> m_vecSpritesDizzy;

	std::vector<int> m_vecNumberCoinsForTransitionNextLevel;

	int m_countSpriteInVectorWalk;
	int m_countSpriteInVectorAttack;
	int m_countSpriteInVectorRun;
	int m_countSpriteInVectorDizzy;
	int m_countSpriteInVectorDie;
	int m_countSpriteInVectorFall;

	std::string m_typeHero;

	int m_attack;
	int m_health;
	int m_coins;
};

#endif