#ifndef __BOT_BULLET_GRAPHIC_COMPONENT_H__
#define __BOT_BULLET_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class BotBulletGraphicComponent : public GraphicComponent
{
public:
	BotBulletGraphicComponent(int attack, const std::string& typeObject);
	BotBulletGraphicComponent(BotBulletGraphicComponent& bullet);

	virtual void Update(Monster& hero, GameScene& scene);
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);

	void LoadBulletNormal();
	void LoadBomb();

	~BotBulletGraphicComponent();

public:
	cocos2d::Point	m_position;
	std::string		m_typeObject;
	int				m_attack;

	std::string		m_strFilename;
};

#endif