#ifndef __TRANSITION_MAIN_SCENE_H__
#define __TRANSITION_MAIN_SCENE_H__

#include "cocos2d.h"

class Monster;

class TransitionMainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene(int coin, int life, std::vector<int>& vecWeapon);
	virtual bool init();
	~TransitionMainScene();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	CREATE_FUNC(TransitionMainScene);
	
	static int m_sCoin;
	static int m_sLife;
	static std::vector<int> m_sVecWeapon;

	cocos2d::Sprite* m_spriteCoin;
	cocos2d::Sprite* m_spriteLife;
	cocos2d::Sprite* m_spriteWeapon;

	int m_quentityCounter;

	std::vector<int>	m_vecWeapon;
	int					m_coin;
	int					m_life;

};

#endif // __TRANSITION_SCENE_H__
