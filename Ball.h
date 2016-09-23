#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball 
{
public:
	Ball(cocos2d::Layer *layer);
	void SetGoToLeft(bool goToLeft);
	void Falling();

public:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;

	cocos2d::Sprite *m_ball;

	bool m_goToLeft;

};

#endif // __BALL_H__
