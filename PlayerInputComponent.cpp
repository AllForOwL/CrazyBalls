#include "PlayerInputComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"

PlayerInputComponent::PlayerInputComponent()
{
	m_keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
}

/*virtual*/ void PlayerInputComponent::Update(Monster& hero)
{
	switch (m_keyCode)
	{
		case EventKeyboard::KeyCode::KEY_F:
		{
			hero.CreateBulletsForFire();
			m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;
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
		case EventKeyboard::KeyCode::KEY_CAPITAL_R:
		{
			hero.m_stateButtonFire = Monster::StateButtonFire::BUTTON_STATE_RELEASE;

			m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;

			break;
		}
		case EventKeyboard::KeyCode::KEY_ENTER:
		{
			Rect _rectButton	= hero.m_graphicComponentButtonFire->getBoundingBox();
			Rect _rectHero		= hero.m_graphicComponentHero->getBoundingBox();

			if (_rectButton.containsPoint(m_locationTouch))
			{
				hero.CreateBulletsForFire();
			}
			else if (_rectHero.containsPoint(m_locationTouch))
			{
				hero.m_stateHero	= Monster::StateHero::HERO_STATE_CHANGE_WEAPON;
				hero.m_stateBonus	= Monster::StateBonus::BONUS_WEAPON;
			}

			m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;

			break;
		}
		
	}
}

/*virtual*/ bool PlayerInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_locationTouch = touch->getLocation();
	
	m_keyCode = EventKeyboard::KeyCode::KEY_ENTER;

	return true;
}

/*virtual*/ void PlayerInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	auto _locationTouchNow		= touch->getLocation();
	auto _locationTouchStart	= touch->getStartLocation();

	if (_locationTouchNow > _locationTouchStart)
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
	}
	else
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	}
}

/*virtual*/ void PlayerInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_keyCode = EventKeyboard::KeyCode::KEY_CAPITAL_R;
}

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