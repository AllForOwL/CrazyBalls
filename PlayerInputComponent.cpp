#include "PlayerInputComponent.h"
#include "WeaponGraphicComponent.h"
#include "PlayerBulletGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"

const int CNT_OPACITY_PRESS_FIRE	= 60;
const int CNT_OPACITY_RELEASE_FIRE	= 200;

PlayerInputComponent::PlayerInputComponent()
{
	m_keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;

	m_btnFire = Sprite::create("res/Bonus/Ruby.png");

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	Size _sizeBtn = m_btnFire->getContentSize();

	m_btnFire->setScale(_visibleSize.width / _sizeBtn.width / 6,
		_visibleSize.height / _sizeBtn.height / 6);

	_sizeBtn.width = m_btnFire->getScaleX();
	_sizeBtn.height = m_btnFire->getScaleY();

	cocos2d::Point _positionBtn = cocos2d::Point(_visibleSize.width - _sizeBtn.width - 30,
		_sizeBtn.height + 30);
	m_btnFire->setPosition(_positionBtn);
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
			m_locationTouch = Vec2::ZERO;
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

/*virtual*/ void PlayerInputComponent::AddButtonFire(GameScene& scene)
{
	scene.addChild(m_btnFire);
}

/*virtual*/ bool PlayerInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_locationTouch = touch->getLocation();
	Rect _rectBtnFire = m_btnFire->getBoundingBox();

	if (_rectBtnFire.containsPoint(m_locationTouch))
	{
		m_keyCode = EventKeyboard::KeyCode::KEY_F;
		m_btnFire->setOpacity(CNT_OPACITY_PRESS_FIRE);
	}

	return true;
}

/*virtual*/ void PlayerInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Size _visibleSize = Director::getInstance()->getVisibleSize();
	
	auto _locationTouchNow		= touch->getLocation();
	auto _locationTouchPrevious = touch->getPreviousLocation();

	if (_locationTouchNow > _locationTouchPrevious)
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
	if (m_btnFire->getOpacity() == CNT_OPACITY_PRESS_FIRE)
	{
		m_btnFire->setOpacity(CNT_OPACITY_RELEASE_FIRE);
	}

	m_keyCode = EventKeyboard::KeyCode::KEY_TILDE;
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