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
	
	static cocos2d::Scene *createScene(bool nextLevel, int coin, int life, std::vector<int>& vecNameWeapon);
	virtual bool init();
	
	void update		(float dt);
	void SpawnEnemyMeteor		(float dt);
	void SpawnEnemyAirplane(float dt);
	void SpawnBonus	(float dt);
	
	void LoadLevel();
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
	
	static int					m_level;
	static int					m_coin;
	static int					m_life;
	static std::vector<int>		m_vecNameWeapon;

	GameLayer*					m_gameLayer;
	std::shared_ptr<Monster>	m_hero;
	std::shared_ptr<GraphicComponent>	m_graphicComponentHero;
	std::shared_ptr<GraphicComponent>	m_graphicComponentWeapon;
	std::shared_ptr<GraphicComponent>	m_graphicComponentButtonFire;
	std::shared_ptr<InputComponent>		m_inputComponent;
	std::shared_ptr<GameObjectMonster>	m_gameObjectMonster;
	std::shared_ptr<GraphicComponent>	m_objectMonster;
	std::shared_ptr<InputComponent>		m_botInputComponent;
	std::shared_ptr<PhysicComponent>	m_physicComponent;
	std::shared_ptr<BonusGraphicComponent>		m_bonusGraphicComponent;

	std::vector<std::string>	m_vecNameBackground;
	cocos2d::Sprite*			m_btnFire;
	float						m_widthBackground;
	int							m_countLevel;

	Sprite* m_background;
};

#endif // __GAME_SCENE_H__
