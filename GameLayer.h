#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class Monster;

class GameLayer : public cocos2d::Layer
{
public:
	// methods
	virtual bool init();

	void Update(Monster& hero);

	void GoToPause(cocos2d::Ref* ref);

	CREATE_FUNC(GameLayer);

public:
	cocos2d::Label* m_lblAttackHero;
	cocos2d::Label* m_lblHealthHero;
	cocos2d::Label* m_lblCoinsHero;
};

#endif // __GAME_LAYER_H__
