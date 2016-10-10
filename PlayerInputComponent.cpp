#include "PlayerInputComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "Monster.h"

PlayerInputComponent::PlayerInputComponent()
{
	m_keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
}

/*virtual*/ void PlayerInputComponent::Update(Monster& hero)
{
	switch (m_keyCode)
	{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_WALK;
			break;
		}
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
		    hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP;
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_FALL;
			break;
		}
		case EventKeyboard::KeyCode::KEY_A:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_ATTACK;
			break;
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_RUN;
			break;
		}
		case EventKeyboard::KeyCode::KEY_F:
		{
			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_FIRE;
			m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;
			break;
		}
		case EventKeyboard::KeyCode::KEY_U:
		{
			hero.m_stateBullet = Monster::StateBullet::BULLET_STATE_FIRE_UP;
			break;
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_CHANGE_WEAPON;
			break;
		}
		case EventKeyboard::KeyCode::KEY_B:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_CHANGE_BULLET;
			break;
		}
	}
}

/*virtual*/ bool PlayerInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_keyCode = EventKeyboard::KeyCode::KEY_F;

	return true;
}

/*virtual*/ void PlayerInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	auto _locationTouch = touch->getLocation();

	if (_locationTouch.y > _visibleSize.height / 2)
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
	}
	else if (_locationTouch.y < _visibleSize.height / 2)
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	}

}

/*virtual*/ void PlayerInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;
}

/*virtual*/ /*void PlayerInputComponent::onTouchMoved(cocos2d::Touch* moved, cocos2d::Event* event)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();

	auto _location = moved->getLocation();

	if (_location.y > _visibleSize.width / 2)
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
	}
	else
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	}

	return true;
}*/

/*virtual*/ void PlayerInputComponent::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_keyCode = keyCode;
}

/*virtual*/ void PlayerInputComponent::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

PlayerInputComponent::~PlayerInputComponent()
{

}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає дані з клавіатури
	Monster				- контейнер для цих компонентів
*/
/* Поле ділится на 2 рівних частини. Перша - поле гравця. Друга - ворогів, яка ще поділена на рівні частини, так, що ці утворюють стовпці і рядки, отже виходить квадратне поле. 
   Через Spawn на полі з₴'являються вороги, які протягом певного інтервалу просто лежать на полі, а після нього стріляють в гравця, якому потрібно не прогавати цей момент оскільки 
   на полі їх буде кілька.
 */

	/*Потрібно виконати     24:09:2016*/
	
/*
	1) Через певний час каміння летить по герою і завдає йому певний damage:
		- час для кожного різний;
		- damage різний;
*/