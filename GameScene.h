#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Monster.h"
#include "GraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameObjectMonster.h"
#include "GameLayer.h"
#include "BonusGraphicComponent.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
	// methods
	
	static cocos2d::Scene *createScene(
										bool nextLevel, 
										int  coin, 
										int  life
									   );
	virtual bool init();
	
	void update				(float dt);
	void SpawnEnemyMeteor	(float dt);
	void SpawnEnemyAirplane	(float dt);
	
	void LoadFileNameBackground();
	void SetBackground();

	CREATE_FUNC(GameScene);

	~GameScene();

public:
	cocos2d::PhysicsWorld* m_sceneWorld;

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world)
	{
		m_sceneWorld = world;
	}
	
	static int	m_level;
	static int	m_coin;
	static int	m_life;

	GameLayer*			m_gameLayer;

	Monster*					m_hero;
	BonusGraphicComponent*		m_bonusGraphicComponent;
	GraphicComponent*	m_graphicComponentHero;
	GraphicComponent*	m_graphicComponentWeapon;
	GraphicComponent*	m_graphicComponentButtonFire;
	InputComponent*		m_inputComponent;
	GameObjectMonster*	m_gameObjectMonster;
	GraphicComponent*	m_objectMonster;
	InputComponent*		m_botInputComponent;
	PhysicComponent*	m_physicComponent;

	std::vector<std::string>	m_vecNameBackground;
	cocos2d::Sprite*			m_btnFire;
	float						m_widthBackground;
	int							m_countLevel;

	Sprite* m_background;

	Size m_visibleSize;

};

#endif // __GAME_SCENE_H__
