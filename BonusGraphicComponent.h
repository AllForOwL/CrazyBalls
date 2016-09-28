#ifndef __BONUS_GRAPHIC_COMPONENT_H__
#define __BONUS_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class BonusGraphicComponent : public GraphicComponent
{
public:
	BonusGraphicComponent();
	//BonusGraphicComponent(int attack, const std::string& typeObject);
	//BonusGraphicComponent(BonusGraphicComponent& bonus);

	virtual void		Update(Monster& hero, GameScene& scene);
	virtual int			GetValue()  const;
	virtual int			GetAttack() const;
	virtual int			GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool		Dead(int wounded);
	virtual void		ChangeCoins(int coins);
	virtual bool		Winner() const;

	void AddBonus(int typeObject);
	void LoadNameOpenCakset();
	void ShowBonusAnimation(float dt);

	~BonusGraphicComponent();

public:
	int			m_attack;
	std::string m_typeObject;
	std::string m_strFilename;
	bool		m_openCasket;
	bool		m_actived;
	int			m_indexInVector;
	bool		m_showAnimation;
	int			m_interval;


	std::vector<std::string> m_vecNameSpritesOpenCasket;
};

#endif