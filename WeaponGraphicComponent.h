#ifndef __WEAPON_GRAPHIC_COMPONENT_H__
#define __WEAPON_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class WeaponGraphicComponent : public GraphicComponent
{
public:
	WeaponGraphicComponent(int attack, const std::string& typeObject);
	WeaponGraphicComponent(WeaponGraphicComponent& weapon);

	virtual void Update(Monster& hero, GameScene& scene);

	virtual int GetAttack() const;
	virtual std::string GetTypeObject() const;
	
	virtual void DescreaseQuentityBullet();
	virtual int  GetQuentityBullet() const;

	~WeaponGraphicComponent();

public:
	int			m_speedBullet;
	int			m_attack;
	std::string m_typeObject;
	
	std::string m_strFilename;

	int			m_quentityBullet;

};

#endif