#ifndef __PLAYER_INPUT_COMPONENT_H__
#define __PLAYER_INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "Monster.h"
#include "InputComponent.h"

using namespace std;
using namespace cocos2d;

class PlayerInputComponent : public InputComponent
{
public:

	enum StateInput
	{
		STATE_FIRE,
		STATE_CHECK_INPUT_FOR_FIRE,
		STATE_HERO_UP,
		STATE_HERO_DOWN,
		STATE_REST
	};

	virtual void Update(Monster& hero);
	
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	PlayerInputComponent();
	~PlayerInputComponent();

public:
	StateInput m_stateInput;
	cocos2d::Vec2 m_locationTouch;
};

#endif