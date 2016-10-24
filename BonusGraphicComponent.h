#ifndef __BONUS_GRAPHIC_COMPONENT_H__
#define __BONUS_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class BonusGraphicComponent : public GraphicComponent
{
public:
	
	enum TypeBonus
	{
		COIN,
		POWER,
		ARMOR,
		BULLET_SPEED,
		BULLET_QUENTITY
	};
	
	enum StateBonus
	{
		ACTIVE,
		NOT_ACTIVE,
		SHOW,
		HIDE,
		DEATH
	};

	BonusGraphicComponent();
	
	virtual void		Update(Monster& hero, GameScene& scene);
	virtual std::string GetTypeObject() const;
		
	void AddBonus(float dt);

	std::chrono::time_point<std::chrono::system_clock> GetTime();

	void SetPropertiesBonus(const std::string& i_nameSprites, const std::string& i_typeBonus);
	void SetPosition();

	~BonusGraphicComponent();

public:
	Size		m_visibleSize;
	std::string m_typeObject;
	StateBonus  m_stateBonus;
	std::chrono::time_point<std::chrono::system_clock> m_secondBeginActive;

	int m_secondEndActive;
};

#endif