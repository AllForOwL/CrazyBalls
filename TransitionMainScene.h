#ifndef __TRANSITION_MAIN_SCENE_H__
#define __TRANSITION_MAIN_SCENE_H__

#include "cocos2d.h"

class Monster;

class TransitionMainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	CREATE_FUNC(TransitionMainScene);

	cocos2d::Sprite* m_spriteCoin;
	cocos2d::Sprite* m_spriteLife;
	cocos2d::Sprite* m_spriteWeapon;
};

#endif // __TRANSITION_SCENE_H__
