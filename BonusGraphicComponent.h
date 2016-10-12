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
	
	virtual void		Update(Monster& hero, GameScene& scene);
	virtual int			GetValue()  const;
	virtual int			GetAttack() const;
	virtual int			GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool		Dead(int wounded);
	virtual void		ChangeCoins(int coins);
	virtual bool		Winner() const;

	virtual void SetSpeedBullet(int speed);
	virtual int  GetSpeedBullet() const;

	virtual void DescreaseQuentityBullet();
	virtual int  GetQuentityBullet() const;

	virtual void ChangeHealth(int health);

	virtual void SetTargetPointForBullet(cocos2d::Point point);
	virtual void SetTargetPosition_YForHero(int target_y);
	
	void AddBonus(int typeObject);
	void LoadNameOpenCakset(const std::string& typeCasket);
	void ShowBonusAnimation(float dt);

	void AddSuperBonus(float dt);
	void LoadNameSpritesSuperBonus();

	std::chrono::time_point<std::chrono::system_clock> GetTime();

	~BonusGraphicComponent();

public:
	int			m_attack;
	std::string m_typeObject;
	std::string m_strFilename;
	bool		m_openCasket;
	bool		m_actived;
	int			m_indexInVector;
	int			m_indexInVectorAnimation;
	bool		m_showAnimation;
	int			m_interval;

	std::vector<std::string> m_vecNameSpritesOpenCasket;

	std::vector<std::string> m_vecNameSpritesSuperBonus;

	std::chrono::time_point<std::chrono::system_clock> m_BeginSecond;

};

#endif