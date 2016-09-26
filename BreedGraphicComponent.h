#ifndef __BREED_GRAPHIC_COMPONENT_H__
#define __BREED_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace std;
using namespace cocos2d;

class Monster;

class BreedGraphicComponent : public GraphicComponent
{ 
public:

	enum StateEnemy
	{
		ENEMY_STATE_FIRE,
		ENEMY_STATE_MOVE,
		ENEMY_STATE_WOUNDED,
		ENEMY_STATE_DEATH,
		ENEMY_STATE_NOTHING
	};

	BreedGraphicComponent(int attack, int health, const std::string& typeObject);
	BreedGraphicComponent(BreedGraphicComponent& breed);

	virtual void Update(Monster& hero, GameScene& scene);

	virtual int GetValue()  const;
	virtual int GetAttack() const;
	virtual int GetHealth() const;
	virtual std::string GetTypeObject() const;
	virtual bool Dead(int wounded);
	virtual void ChangeCoins(int coins);
	virtual bool Winner() const;


	void		Fire(Point i_position);
	void		Move();
	void		Attack();
	void		Wounded();
	bool		Death();

	double GetTime();

	~BreedGraphicComponent();

public:
	int m_attack;
	int m_health;
	std::string m_typeObject;
	
	std::vector<std::string> m_vecDefaultNamesMove;
	std::vector<std::string> m_vecDefaultNamesFire;
	std::vector<std::string> m_vecDefaultNamesDeath;

	int	m_countDefaultSpriteInMove;
	int m_countDefaultSpriteInFire;
	int m_countDefaultSpriteInDeath;

	StateEnemy	m_stateEnemy;
	double		m_BeginSecond;
	double		m_FireSecond;
	int			m_scale_x;
	Point		m_pointBeginPosition;
	int			m_value;
};
#endif