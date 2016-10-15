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
	virtual ~InputComponent() {};

	virtual void Update(Monster& heroes) = 0;

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		return true;
	}
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		
	}
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
	{

	}
};

#endif