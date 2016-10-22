#include "BonusGraphicComponent.h"
#include "Monster.h"
#include "GameScene.h"
#include "constants.h"

const int CNT_SECOND_VISIBLE_SUPER_BONUS = 10;

BonusGraphicComponent::BonusGraphicComponent()
{
	this->initWithFile("res/Bonus/powerupBlue_bolt.png");
	
	m_visibleSize		= Director::getInstance()->getVisibleSize();
	Size _sizeBonus		= this->getContentSize();

	this->setScale(	m_visibleSize.width  / _sizeBonus.width / 20,
					m_visibleSize.height / _sizeBonus.height / 20
				  );

	auto physicBodyBonus = PhysicsBody::createBox(this->getBoundingBox().size);
	physicBodyBonus->setContactTestBitmask(true);
	physicBodyBonus->setCollisionBitmask(BONUS_COLLISION_BITMASK);
	physicBodyBonus->setDynamic(false);
	this->setPhysicsBody(physicBodyBonus);
}

void BonusGraphicComponent::SetPropertiesBonus(const std::string& i_nameSprites, const std::string& i_typeBonus)
{
	this->setTexture(CCTextureCache::sharedTextureCache()->addImage(i_nameSprites));
	this->m_typeObject = i_typeBonus;
}

void BonusGraphicComponent::SetPosition()
{
	Vec2 _positionBonus = Point::ZERO;

	int _orderTop		= m_visibleSize.width - this->getBoundingBox().size.width;
	int _orderBottom	= m_visibleSize.width / 2;	
	_positionBonus.x	= rand() % _orderTop + _orderBottom;

	_orderTop			= m_visibleSize.height - this->getBoundingBox().size.height;
	_orderBottom		= this->getBoundingBox().size.height;
	_positionBonus.y	= rand() % _orderTop + _orderBottom;

	this->setPosition(_positionBonus.x, _positionBonus.y);
}

void BonusGraphicComponent::AddBonus()
{
	int _typeBonus = rand() % 3 + 0;

	switch (_typeBonus)
	{
		case TypeBonus::COIN:
		{
			SetPropertiesBonus("res/Bonus/powerupBlue_star.png", CNT_NAME_BONUS_COIN);
			break;
		}
		case TypeBonus::POWER:
		{
			SetPropertiesBonus("res/Bonus/pill_blue.png", CNT_NAME_BONUS_POWER);
			break;
		}
		case TypeBonus::ARMOR:
		{
			SetPropertiesBonus("res/Bonus/powerupBlue_shield.png", CNT_NAME_BONUS_ARMOR);
			break;
		}

		case TypeBonus::BULLET_SPEED:
		{
			SetPropertiesBonus("res/Bonus/powerupBlue_bolt.png", CNT_NAME_BONUS_BULLET_SPEED);
			break;
		}
		case TypeBonus::BULLET_QUENTITY:
		{
			SetPropertiesBonus("res/Bonus/things_bronze.png", CNT_NAME_BONUS_BULLET_QUENTITY);
			break;
		}
		
	default:
		break;
	}

	SetPosition();
}

std::chrono::time_point<std::chrono::system_clock> BonusGraphicComponent::GetTime()
{
	std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now();

	return _time;
}

/*virtual*/ void BonusGraphicComponent::Update(Monster& hero, GameScene& scene)
{

}

/*virtual*/ std::string BonusGraphicComponent::GetTypeObject() const
{
	return m_typeObject;
}

BonusGraphicComponent::~BonusGraphicComponent()
{
	CCLOG("destructor bonus");
}

// ***Bonus element*** //
/*
	 casket:
		+ coins;
		+- clothes;
	+ all type weapon;
	- up/down speed;
	+ all type bullet;
*/