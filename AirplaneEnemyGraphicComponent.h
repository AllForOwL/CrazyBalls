#ifndef __AIRPLANE_ENEMY_GRAPHIC_COMPONENT_H__
#define __AIRPLANE_ENEMY_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"
#include <ctime>

using namespace std;
using namespace cocos2d;

class Monster;

class AirplaneEnemyGraphicComponent : public GraphicComponent
{ 
public:
	AirplaneEnemyGraphicComponent(int i_attack, int i_armor, int i_health, const std::string& i_typeObject);
	AirplaneEnemyGraphicComponent(const AirplaneEnemyGraphicComponent& copyObject);

	void SetPropertiesAirplane();

	int GetAttack() const;
	int ChangeHealth();
	std::string GetTypeObject() const;

private:
	int			m_attack;
	int			m_armor;
	int			m_health;
	std::string m_typeObject;

};
#endif