#include "Ball.h"


#define COLLISION_BITMASK_BALL	0X000003

USING_NS_CC;

Ball::Ball(cocos2d::Layer *layer)
{
	m_visibleSize	= Director::getInstance()->getVisibleSize();
	m_origin		= Director::getInstance()->getVisibleOrigin();

	m_goToLeft = false;

	m_ball = Sprite::create("imgBall.png");
	m_ball->setPosition(m_visibleSize.width / 2,
						m_visibleSize.height / 2 + 100);

	auto bodyBall = PhysicsBody::createCircle(m_ball->getContentSize().width / 2);
	bodyBall->setCollisionBitmask(COLLISION_BITMASK_BALL);
	bodyBall->setContactTestBitmask(true);
	m_ball->setPhysicsBody(bodyBall);

	layer->addChild(m_ball, 100);
}

void Ball::SetGoToLeft(bool goToLeft)
{
	if (goToLeft)
	{
		m_goToLeft = true;
	}
}

void Ball::Falling()
{
	if (m_goToLeft)
	{
		m_ball->setPosition(m_ball->getPosition().x + 1,
							m_ball->getPosition().y - 1
							);
	}
	else
	{
		m_ball->setPosition(m_ball->getPosition().x - 1,
							m_ball->getPosition().y - 1
							);
	}
}