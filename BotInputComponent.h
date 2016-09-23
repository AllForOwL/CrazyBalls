#ifndef __BOT_INPUT_COMPONENT_H__
#define __BOT_INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "Monster.h"
#include "InputComponent.h"

using namespace std;
using namespace cocos2d;

class BotInputComponent : public InputComponent
{
public:
	BotInputComponent();

	virtual void Update(Monster& heroes);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	~BotInputComponent();
};

#endif