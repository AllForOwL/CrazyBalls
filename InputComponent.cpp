#include "InputComponent.h"
#include "Monster.h"

InputComponent::InputComponent()
{
	m_keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
}

EventKeyboard::KeyCode& InputComponent::GetActiveKey()
{
	return m_keyCode;
}

void InputComponent::update(Monster& heroes)
{
	switch (m_keyCode)
	{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			heroes.SetState(heroes.STATE_WALK);
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			heroes.SetState(heroes.STATE_JUMP);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F:
		{
			heroes.SetState(heroes.STATE_FIRE);
			break;
		}
	}
}

void InputComponent::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_keyCode = keyCode;
}

void InputComponent::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	// додати код для спрацювання при відпусканні клавіші
}

InputComponent::~InputComponent()
{

}
