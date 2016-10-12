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

	~BotInputComponent();
};

#endif