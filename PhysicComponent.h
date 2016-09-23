#ifndef __PHYSIC_COMPONENT_H__
#define __PHYSIC_COMPONENT_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameScene;
class Monster;

class PhysicComponent
{
public:
	enum StatePhysic
	{
		STATE_NOTHING,
		STATE_WOUNDED_ENEMY,
		STATE_WOUNDED_HERO
	};

	PhysicComponent();

	void Update(Monster& hero, GameScene& scene);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	~PhysicComponent();

private:
	StatePhysic						m_statePhysic;
	int								m_countElementInVector;
	cocos2d::Vec2					m_positionCollision;
	int								m_tagForDelete;

	int m_TagBullet;
	int m_TagEnemy;
	int m_TagHero;
};

#endif