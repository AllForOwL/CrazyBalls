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
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);

	void LoadSpritesForHell();

	~HeroGraphicComponent();

public:
	std::vector<std::string> m_vecSpritesWalk;
	std::vector<std::string> m_vecSpritesAttack;
	std::vector<std::string> m_vecSpritesRun;
	std::vector<std::string> m_vecSpritesFall;
	std::vector<std::string> m_vecSpritesDie;
	std::vector<std::string> m_vecSpritesDizzy;

	int m_countSpriteInVectorWalk;
	int m_countSpriteInVectorAttack;
	int m_countSpriteInVectorRun;

	std::string m_typeHero;

	int m_attack;
	int m_health;

	LabelProtocol* m_lblAttack;
	LabelProtocol* m_lblHealth;
};

#endif