#include "ButtonGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"

const int CNT_OPACITY_PRESS_FIRE	= 60;
const int CNT_OPACITY_RELEASE_FIRE	= 200;

ButtonGraphicComponent::ButtonGraphicComponent()
{
	this->initWithFile("res/Bonus/Ruby.png");

	Size _visibleSize = Director::getInstance()->getVisibleSize();
	Size _sizeBtn = this->getContentSize();

	this->setScale(_visibleSize.width / _sizeBtn.width / 6,
					_visibleSize.height / _sizeBtn.height / 6);

	_sizeBtn = this->getBoundingBox().size;

	cocos2d::Point _positionBtn = cocos2d::Point(_visibleSize.width - _sizeBtn.width / 2,
												_sizeBtn.height / 2);
	this->setPosition(_positionBtn);
}

/*virtual*/ void ButtonGraphicComponent::Update(Monster& hero, GameScene& scene)
{
	if (!this->getParent())
	{
		scene.addChild(this);
	}

	switch (hero.m_stateButtonFire)
	{
		case Monster::StateButtonFire::BUTTON_STATE_FIRE:
		{
			this->setOpacity(CNT_OPACITY_PRESS_FIRE);
			break;
		}
		case Monster::StateButtonFire::BUTTON_STATE_RELEASE:
		{
			this->setOpacity(CNT_OPACITY_RELEASE_FIRE);
			break;
		}
		default:
			break;
	}
}

ButtonGraphicComponent::~ButtonGraphicComponent()
{
	CCLOG("destructor buttongraphic");
}