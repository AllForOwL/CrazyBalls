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
	virtual void Update(Monster& hero);
	
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	PlayerInputComponent();
	~PlayerInputComponent();

public:
	EventKeyboard::KeyCode m_keyCode;
};

#endif