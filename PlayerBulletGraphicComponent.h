#ifndef __PLAYER_BULLET_GRAPHIC_COMPONENT_H__
#define __PLAYER_BULLET_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class PlayerBulletGraphicComponent : public GraphicComponent
{
public:

	enum StateBullet
	{
		BULLET_STATE_FIRE,
		BULLET_STATE_FIRE_UP,
		BULLET_STATE_REST,
		BULLET_STATE_TARGET,
		BULLET_STATE_DEATH
	};

	PlayerBulletGraphicComponent(int i_ID, int attack, const std::string& typeObject);
	PlayerBulletGraphicComponent(PlayerBulletGraphicComponent& bullet);

	virtual void Update(Monster& hero, GameScene& scene);

	virtual int GetAttack() const;
	virtual std::string GetTypeObject() const;
	
	virtual void SetSpeedBullet(int speed);
	virtual int GetSpeedBullet() const;

	virtual void SetTargetPointForBullet(cocos2d::Point point);
	
	void LoadBulletNormal();

	virtual void HideObject();

	void ChangeStateBullet(const StateBullet& newState);

	virtual int GetID() const;
	
	virtual bool Remove() const;

	~PlayerBulletGraphicComponent();

public:
	StateBullet		m_stateBullet;
	Size			m_visibleSize;
	int				m_ID;
	std::map<int, ComponentHero*>::iterator m_iterator;
				

	int m_speed;
	cocos2d::Point	m_pointBegin;
	std::string		m_typeObject;
	int				m_attack;

	std::string		m_strFilename;

	bool m_isBody;

	cocos2d::Point	m_targetPoint;

	bool m_remove;
};

#endif