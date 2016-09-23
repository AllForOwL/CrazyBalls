#ifndef __INPUT_COMPONENT_H__
#define __INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "Monster.h"

using namespace cocos2d;
using namespace std;

// intarface for other input classes
class InputComponent
{
public:
	virtual void Update(Monster& heroes) = 0;

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) = 0;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) = 0;

	virtual ~InputComponent() {};

public:
	EventKeyboard::KeyCode m_keyCode;
};

#endif