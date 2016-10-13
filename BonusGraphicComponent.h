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
	virtual std::string GetTypeObject() const;
		
	void AddBonus(int typeObject);
	void LoadNameOpenCakset(const std::string& typeCasket);
	void ShowBonusAnimation(float dt);

	void AddSuperBonus(float dt);
	void LoadNameSpritesSuperBonus();

	std::chrono::time_point<std::chrono::system_clock> GetTime();

	virtual void HideObject();
	virtual void StartShowAnimation();

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