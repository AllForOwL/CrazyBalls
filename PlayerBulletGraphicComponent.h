#ifndef __PLAYER_BULLET_GRAPHIC_COMPONENT_H__
#define __PLAYER_BULLET_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class PlayerBulletGraphicComponent : public GraphicComponent
{
public:
	PlayerBulletGraphicComponent(int attack, const std::string& typeObject);
	PlayerBulletGraphicComponent(PlayerBulletGraphicComponent& bullet);

	virtual void Update(Monster& hero, GameScene& scene);

	virtual int GetValue()  const;
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);
	virtual void ChangeCoins(int coins);
	virtual bool Winner() const;

	virtual void SetSpeedBullet(int speed);
	virtual int GetSpeedBullet() const;

	virtual void DescreaseQuentityBullet();
	virtual int  GetQuentityBullet() const;

	void LoadBulletNormal();
	~PlayerBulletGraphicComponent();

private:
	int m_speed;
	cocos2d::Point	m_position;
	std::string		m_typeObject;
	int				m_attack;

	std::string		m_strFilename;

	bool m_isBody;
};

#endif