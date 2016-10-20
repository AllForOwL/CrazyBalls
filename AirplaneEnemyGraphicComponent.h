#ifndef __AIRPLANE_ENEMY_GRAPHIC_COMPONENT_H__
#define __AIRPLANE_ENEMY_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"
#include <ctime>

using namespace std;
using namespace cocos2d;

class Monster;
class BotBulletGraphicComponent;

class AirplaneEnemyGraphicComponent : public GraphicComponent
{ 
public:

	struct PropertiesAirplane
	{
		int m_attack;
		int m_armor;
		int m_health;
		int m_spawnShot;

		PropertiesAirplane() :
							m_attack(0),
							m_armor(0),
							m_health(0),
							m_spawnShot(0)
		{

		}
	};

	enum StateAirplane
	{
		STATE_CREATE_BULLETS,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_DEATH,
		STATE_REST
	};

	AirplaneEnemyGraphicComponent(const std::string& i_typeObject);
	AirplaneEnemyGraphicComponent(const AirplaneEnemyGraphicComponent& copyObject);
	~AirplaneEnemyGraphicComponent();

	virtual void Update(Monster& hero, GameScene& scene);

	virtual void CauseDamage(const int& i_numberDamageHealth, const int& i_numberDamageArmor);

	void SetPropertiesAirplane(const std::string& i_filename);
	void DetermineTypeObject();

	int GetAttack() const;
	int GetArmor() const;
	int GetHealth() const;
	std::string GetTypeObject() const;

	void SetStateCreateBullets(float dt);
	void CreateBullets();
	void Move();

	void LoadValueProperties();

public:
	static std::vector<PropertiesAirplane> m_vecAirplaneBlack;
	static std::vector<PropertiesAirplane> m_vecAirplaneBlue;
	static std::vector<PropertiesAirplane> m_vecAirplaneGreen;
	static std::vector<PropertiesAirplane> m_vecAirplaneRed;

	int			m_attack;
	int			m_armor;
	int			m_health;
	std::string m_typeObject;

	Size			m_visibleSize;
	int				m_timeSpawnShot;
	StateAirplane	m_stateAirplane;

	std::vector<BotBulletGraphicComponent*> m_vecBullet;
};
#endif