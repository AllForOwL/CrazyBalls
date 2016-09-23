#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Monster.h"
#include "GraphicComponent.h"
#include "PlayerInputComponent.h"
#include "GameObjectMonster.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
	// methods
	static cocos2d::Scene *createScene();
	virtual bool init();
	void update(float dt);
	void Spawn(float dt);
	void LoadLevel();
	void LoadFileBackground();

	CREATE_FUNC(GameScene);

	~GameScene();

public:
	cocos2d::PhysicsWorld* m_sceneWorld;

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world)
	{
		m_sceneWorld = world;
	}

	cocos2d::Sprite* m_background;

	cocos2d::Sprite* m_spriteHero;
	cocos2d::Layer*  m_layer;

	Monster*			m_hero;
	GraphicComponent*	m_graphicComponentHero;
	GraphicComponent*	m_graphicComponentWeapon;
	GraphicComponent*	m_graphicComponentBullet;
	InputComponent*		m_inputComponent;
	GameObjectMonster*	m_gameObjectMonster;
	GraphicComponent*	m_objectMonster;
	InputComponent*		m_botInputComponent;
	PhysicComponent*	m_physicComponent;

	std::vector<std::string> m_vecSpritesWalk;
	int m_countSpriteInVector;
	int m_countLevel;
	std::vector<cocos2d::Sprite*> m_vecBackground;
	float						  m_widthBackground;
};

#endif // __GAME_SCENE_H__
