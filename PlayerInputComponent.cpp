#include "PlayerInputComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"

PlayerInputComponent::PlayerInputComponent()
{
	m_stateInput = StateInput::STATE_REST;
}

/*virtual*/ void PlayerInputComponent::Update(Monster& hero)
{
	switch (m_stateInput)
	{
		case StateInput::STATE_FIRE:
		{
			hero.CreateBulletsForFire();
			
			break;
		}
		case StateInput::STATE_CHECK_INPUT_FOR_FIRE:
		{
			Rect _rectButton	= hero.m_graphicComponentButtonFire->getBoundingBox();
			Rect _rectHero		= hero.m_graphicComponentHero->getBoundingBox();

			if (_rectButton.containsPoint(m_locationTouch))
			{
				hero.CreateBulletsForFire();
				m_stateInput = StateInput::STATE_FIRE;
			}
			else
			{
				m_stateInput = StateInput::STATE_REST;
			}

			break;
		}
		case StateInput::STATE_HERO_UP:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_UP;
			break;
		}
		case StateInput::STATE_HERO_DOWN:
		{
			hero.m_stateHero = Monster::StateHero::HERO_STATE_JUMP_DOWN;
			break;
		}
	}
}

/*virtual*/ bool PlayerInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_locationTouch = touch->getLocation();
	m_stateInput = StateInput::STATE_CHECK_INPUT_FOR_FIRE;

	return true;
}

/*virtual*/ void PlayerInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	auto _locationTouchNow		= touch->getLocation();
	auto _locationTouchStart	= touch->getStartLocation();

	if (_locationTouchNow > _locationTouchStart)
	{
		m_stateInput = StateInput::STATE_HERO_UP;
	}
	else
	{
		m_stateInput = StateInput::STATE_HERO_DOWN;
	}
}

/*virtual*/ void PlayerInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_stateInput = StateInput::STATE_REST;
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