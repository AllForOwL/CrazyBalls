#include "BotInputComponent.h"
#include "Monster.h"
#include "GameObjectMonster.h"

BotInputComponent::BotInputComponent()
{

}

/*virtual*/ void BotInputComponent::Update(Monster& heroes)
{

}

/*virtual*/ void BotInputComponent::onKeyPressed(EventKeyboard::KeyCode, Event* event)
{

}

/*virtual*/ void BotInputComponent::onKeyReleased(EventKeyboard::KeyCode, Event* event)
{

}

/*virtual*/ bool BotInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

/*virtual*/ void BotInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

/*virtual*/ void BotInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

BotInputComponent::~BotInputComponent()
{

}