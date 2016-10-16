#ifndef __BOT_BULLET_GRAPHIC_COMPONENT_H__
#define __BOT_BULLET_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class BotBulletGraphicComponent : public GraphicComponent
{
public:

	enum StateBullet
	{
		STATE_FIRE,
		STATE_REST,
		STATE_DEATH
	};

	BotBulletGraphicComponent(int i_ID, int attack, const std::string& typeObject);
	BotBulletGraphicComponent(BotBulletGraphicComponent& bullet);

	virtual void Update(Monster& hero, GameScene& scene);
	virtual int GetAttack() const;
	virtual std::string GetTypeObject() const;
	
	void LoadBulletNormal();
	void LoadBomb();

	void ChangeState(const StateBullet& newState);

	~BotBulletGraphicComponent();

public:
	cocos2d::Point	m_position;
	std::string		m_typeObject;
	int				m_attack;
	int				m_ID;

	Size			m_visibleSize;
	std::string		m_strFilename;
	StateBullet		m_stateBullet;
	Point			m_pointBegin;
	int				m_speed;
};

#endif